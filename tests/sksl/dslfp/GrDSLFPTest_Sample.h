

/**************************************************************************************************
 *** This file was autogenerated from GrDSLFPTest_Sample.fp; do not modify.
 **************************************************************************************************/
#ifndef GrDSLFPTest_Sample_DEFINED
#define GrDSLFPTest_Sample_DEFINED

#include "include/core/SkM44.h"
#include "include/core/SkTypes.h"


#include "src/gpu/GrFragmentProcessor.h"

class GrDSLFPTest_Sample : public GrFragmentProcessor {
public:
    static std::unique_ptr<GrFragmentProcessor> Make(std::unique_ptr<GrFragmentProcessor> fp1, std::unique_ptr<GrFragmentProcessor> fp2, std::unique_ptr<GrFragmentProcessor> fp3) {
        return std::unique_ptr<GrFragmentProcessor>(new GrDSLFPTest_Sample(std::move(fp1), std::move(fp2), std::move(fp3)));
    }
    GrDSLFPTest_Sample(const GrDSLFPTest_Sample& src);
    std::unique_ptr<GrFragmentProcessor> clone() const override;
    const char* name() const override { return "DSLFPTest_Sample"; }
private:
    GrDSLFPTest_Sample(std::unique_ptr<GrFragmentProcessor> fp1, std::unique_ptr<GrFragmentProcessor> fp2, std::unique_ptr<GrFragmentProcessor> fp3)
    : INHERITED(kGrDSLFPTest_Sample_ClassID, kNone_OptimizationFlags) {
        this->registerChild(std::move(fp1), SkSL::SampleUsage::PassThrough());
        this->registerChild(std::move(fp2), SkSL::SampleUsage::Explicit());
        this->registerChild(std::move(fp3), SkSL::SampleUsage::VariableMatrix(true));
    }
    std::unique_ptr<GrGLSLFragmentProcessor> onMakeProgramImpl() const override;
    void onGetGLSLProcessorKey(const GrShaderCaps&, GrProcessorKeyBuilder*) const override;
    bool onIsEqual(const GrFragmentProcessor&) const override;
#if GR_TEST_UTILS
    SkString onDumpInfo() const override;
#endif
    GR_DECLARE_FRAGMENT_PROCESSOR_TEST
    using INHERITED = GrFragmentProcessor;
};
#endif