#include <stdint.h>

namespace xym_infer {
namespace ops {
namespace cuda {
using fp32 = float;

void GemmFP32(fp32* mat1, fp32* mat2, fp32* res);

}  // namespace cuda
}  // namespace ops
}  // namespace xym_infer