#include "Segmentation.h"

Segmentation::Segmentation(Scalar min,Scalar max,Mat *Mask)
{
	rgbmin = min;
	rgbmax = max;
	Mascara[0] = Mask[0];
	Mascara[1] = Mask[1];

}
Mat* Segmentation::Segmentation_Result(Mat *frame)
{


   inRange(*frame, rgbmin, rgbmax, segmentacao);
   morphologyEx(segmentacao, segmentacao,MORPH_OPEN, Mascara[0]);
   morphologyEx(segmentacao, segmentacao,MORPH_CLOSE, Mascara[1]);



   return &segmentacao;


}

