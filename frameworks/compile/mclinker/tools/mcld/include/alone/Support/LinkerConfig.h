//===- Linker.h -----------------------------------------------------------===//
//
//                     The MCLinker Project
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef ALONE_SUPPORT_LINKER_CONFIG_H
#define ALONE_SUPPORT_LINKER_CONFIG_H

#include <string>

#include <mcld/LinkerConfig.h>
#include <mcld/Support/TargetRegistry.h>
#include <mcld/LD/DiagnosticLineInfo.h>
#include <mcld/LD/DiagnosticPrinter.h>

namespace alone {

class LinkerConfig {
private:
  //===--------------------------------------------------------------------===//
  // Available Configurations
  //===--------------------------------------------------------------------===//
  const std::string mTriple;
  std::string mSOName;

private:
  //===--------------------------------------------------------------------===//
  // These are generated by LinkerConfig during initialize().
  //===--------------------------------------------------------------------===//
  const mcld::Target *mTarget;
  bool initializeTarget();

  mcld::LinkerConfig *mLDConfig;
  bool initializeLDInfo();

  mcld::DiagnosticLineInfo *mDiagLineInfo;
  mcld::DiagnosticPrinter *mDiagPrinter;
  bool initializeDiagnostic();

public:
  enum ZOptionEnum {
    kCombReloc     = 1 << 0,  ///< [on] -z combreloc, [off] -z nocombreloc
    kDefs          = 1 << 1,  ///< -z defs
    kExecStack     = 1 << 2,  ///< [on] -z execstack, [off] -z noexecstack
    kInitFirst     = 1 << 3,  ///< -z initfirst
    kInterPose     = 1 << 4,  ///< -z interpose
    kLoadFltr      = 1 << 5,  ///< -z loadfltr
    kMulDefs       = 1 << 6,  ///< -z muldefs
    kNoCopyReloc   = 1 << 7,  ///< -z nocopyreloc
    kNoDefaultLib  = 1 << 8,  ///< -z nodefaultlib
    kNoDelete      = 1 << 9,  ///< -z nodelete
    kNoDLOpen      = 1 << 10, ///< -z nodlopen
    kNoDump        = 1 << 11, ///< -z nodump
    kRelro         = 1 << 12, ///< [on] -z relro, [off] -z norelro
    kLazy          = 1 << 13, ///< [on] -z lazy, [off] -z now
    kOrigin        = 1 << 14, ///< -z origin
    kZOptionMask   = 0xFFFF
  };

public:
  //===--------------------------------------------------------------------===//
  // Getters
  //===--------------------------------------------------------------------===//
  inline const std::string &getTriple() const
  { return mTriple; }

  inline const mcld::Target *getTarget() const
  { return mTarget; }

  inline mcld::LinkerConfig* getLDConfig()
  { return mLDConfig; }

  inline const mcld::LinkerConfig* getLDConfig() const
  { return mLDConfig; }

  bool isShared() const;

  inline std::string getSOName() const
  { return mSOName; }

  void setShared(bool pEnable = true);

  void setBsymbolic(bool pEnable = true);

  void setDefineCommon(bool pEnable = true);

  void setSOName(const std::string &pSOName);

  void setDyld(const std::string &pDyld);

  void setSysRoot(const std::string &pSysRoot);

  void setZOption(unsigned int pOptions);

  void addWrap(const std::string &pWrapSymbol);

  void addPortable(const std::string &pPortableSymbol);

  void addSearchDir(const std::string &pDir);

public:
  LinkerConfig(const std::string& pTriple);

  virtual ~LinkerConfig();
};

} // end namespace alone

#endif // ALONE_SUPPORT_LINKER_CONFIG_H
