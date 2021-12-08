/*
 * Copyright 2021 Google LLC
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef skgpu_MtlUtils_DEFINED
#define skgpu_MtlUtils_DEFINED

#include "experimental/graphite/src/ResourceTypes.h"
#include "include/core/SkImageInfo.h"
#include "include/ports/SkCFObject.h"
#include "src/sksl/ir/SkSLProgram.h"

#import <Metal/Metal.h>

namespace SkSL {
class String;
}

namespace skgpu::mtl {

class Gpu;

bool FormatIsDepthOrStencil(MTLPixelFormat);
bool FormatIsDepth(MTLPixelFormat);
bool FormatIsStencil(MTLPixelFormat);

MTLPixelFormat SkColorTypeToFormat(SkColorType);

MTLPixelFormat DepthStencilFlagsToFormat(Mask<DepthStencilFlags>);

/**
 * Produces MSL code generated by SkSLC
 */
bool SkSLToMSL(const Gpu* gpu,
               const SkSL::String& sksl,
               SkSL::ProgramKind kind,
               const SkSL::Program::Settings& settings,
               SkSL::String* msl,
               SkSL::Program::Inputs* outInputs);

sk_cfp<id<MTLLibrary>> CompileShaderLibrary(const Gpu* gpu,
                                            const SkSL::String& msl);

} // namespace skgpu::mtl

#endif // skgpu_MtlUtils_DEFINED
