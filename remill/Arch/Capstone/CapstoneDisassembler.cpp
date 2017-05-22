#include "CapstoneDisassembler.h"

#include <iostream>
#include <sstream>
#include <algorithm>

#include <glog/logging.h>
#include <remill/Arch/Name.h>

namespace remill {

void CapstoneInstructionDeleter(cs_insn *instruction) noexcept {
  if (instruction != nullptr)
    cs_free(instruction, 1);
}

CapstoneDisassembler::CapstoneDisassembler(cs_arch arch, cs_mode mode) : data_(new PrivateData) {
  data_->little_endian = ((mode & CS_MODE_BIG_ENDIAN) == 0);
  data_->disasm_mode = mode;
  data_->architecture = arch;

  CHECK(cs_open(data_->architecture, data_->disasm_mode, &data_->capstone) == CS_ERR_OK)
      << "Failed to initialize the Capstone library!";

  CHECK(cs_option(data_->capstone, CS_OPT_DETAIL, CS_OPT_ON) == CS_ERR_OK)
      << "Failed to set the capstone decoder options!";
}

CapstoneDisassembler::~CapstoneDisassembler() {
  cs_close(&data_->capstone);
}

bool CapstoneDisassembler::Decode(const std::unique_ptr<Instruction> &remill_instr, uint64_t address, const std::string &instr_bytes) const noexcept {
  CapstoneInstructionPtr capstone_instr = Disassemble(address, reinterpret_cast<const std::uint8_t *>(instr_bytes.data()), instr_bytes.size());
  if (!capstone_instr)
    return false;

  if (!ConvertToRemillInstruction(remill_instr, capstone_instr))
    return false;

  return true;
}

CapstoneInstructionPtr CapstoneDisassembler::Disassemble(std::uint64_t address, const std::uint8_t *buffer, std::size_t buffer_size) const noexcept {
  cs_insn *temp_instr;

  if (cs_disasm(data_->capstone, buffer, buffer_size, address, 1, &temp_instr) == 0){
    LOG(FATAL) << "Failed to disassemble code!";
    return nullptr;
  }
  return CapstoneInstructionPtr(temp_instr, CapstoneInstructionDeleter);
}

std::string CapstoneDisassembler::SemanticFunctionName(const CapstoneInstructionPtr &capstone_instr, const std::vector<Operand> &operand_list) const noexcept {
  // in the default implementation we don't need to access the capstone instruction
  static_cast<void>(capstone_instr);

  std::string mnemonic = capstone_instr->mnemonic;
  std::transform(mnemonic.begin(), mnemonic.end(), mnemonic.begin(), ::toupper);

  std::stringstream runtime_function_name;
  runtime_function_name << mnemonic;

  for (const Operand &operand : operand_list) {
    switch (operand.type) {
      case Operand::kTypeInvalid: {
        CHECK(false) << "Invalid operand type";
      }

      case Operand::kTypeRegister: {
        runtime_function_name << "_R" << (operand.reg.size * 8);
        break;
      }

      case Operand::kTypeImmediate: {
        runtime_function_name << "_I" << (operand.imm.is_signed ? "i" : "u") << "64";
        break;
      }

      case Operand::kTypeAddress: {
        runtime_function_name << "_M" << (operand.addr.address_size * 8);
        break;
      }
    }
  }

  return runtime_function_name.str();
}

bool CapstoneDisassembler::ConvertToRemillInstruction(const std::unique_ptr<remill::Instruction> &remill_instr, const CapstoneInstructionPtr &capstone_instr) const noexcept {
  std::stringstream disassembly;
  disassembly << capstone_instr->mnemonic << " " << capstone_instr->op_str;
  remill_instr->disassembly = disassembly.str();
  std::cout << "ConvertToRemillInstruction 1" << std::endl;

  if (data_->architecture == CS_ARCH_ARM)
    remill_instr->arch_name = kArchARM;
  else if (data_->architecture == CS_ARCH_ARM64)
    remill_instr->arch_name = kArchARM64;
  else if (data_->architecture == CS_ARCH_MIPS) {
    if ((data_->disasm_mode & CS_MODE_MIPS64) != 0)
      remill_instr->arch_name = kArchMips64;
    else
      remill_instr->arch_name = kArchMips32;
  }

  remill_instr->pc = capstone_instr->address;
  remill_instr->next_pc = remill_instr->pc + capstone_instr->size;
  remill_instr->operand_size = AddressSize() / 8;
  remill_instr->category = InstructionCategory(capstone_instr);
  remill_instr->branch_taken_pc = 0;
  remill_instr->branch_not_taken_pc = 0;
  remill_instr->is_atomic_read_modify_write = false;

  //
  // convert the operands
  //

  remill_instr->operands.clear();
  CHECK(InstructionOperands(remill_instr->operands, capstone_instr))
      << "Unsupported instruction operand encountered";

  remill_instr->function = SemanticFunctionName(capstone_instr, remill_instr->operands);
  return true;
}

Operand::Action
CapstoneDisassembler::RegisterAccessType(unsigned int register_id, const CapstoneInstructionPtr &capstone_instr) const noexcept {
  Operand::Action action_type = Operand::kActionInvalid;

  for (uint8_t i = 0; i < capstone_instr->detail->regs_read_count; i++) {
  if (capstone_instr->detail->regs_read[i] != register_id)
    continue;

   action_type = Operand::kActionRead;
   break;
  }

  for (uint8_t i = 0; i < capstone_instr->detail->regs_write_count; i++) {
  if (capstone_instr->detail->regs_write[i] != register_id)
    continue;

   action_type = Operand::kActionWrite;
   break;
  }

  return action_type;
}

#define NULL_STRING ""
#define REG_INVALID 0

std::string
CapstoneDisassembler::RegisterName(std::uintmax_t id) const noexcept {
  if(id != REG_INVALID)
    return cs_reg_name(data_->capstone, id);
  return NULL_STRING;
}


}  // remill namespace
