# template_matching
Recognise turbulence signal in AWS GTG forcast

library: OpenCV

First, you need a background image of GTG and the signal image in JPG store in the same file with the c++ code

background.jpg

<img src="https://github.com/caraaaaa/template_matching/blob/master/images/background.jpg" width="50%" height="50%">

feature.jpg

<img src="https://github.com/caraaaaa/template_matching/blob/master/images/feature.jpg" width="7%" height="7%">

Then, you can compile and run the code by:

./MatchTemplate [GTG forcast image in JPG]

<img src="https://github.com/caraaaaa/template_matching/blob/master/images/sample.jpg" width="50%" height="50%">


**Inside code**

1. Invert color of the input image and the background image
<img src="https://github.com/caraaaaa/template_matching/blob/master/images/converted.jpg" width="80%" height="80%">

2. Subtract pixel of the input image from the backgroun image. Invert the input image back to original color
<img src="https://github.com/caraaaaa/template_matching/blob/master/images/Filtered.jpg" width="50%" height="50%">

3. Perform matchTemplate and mark the identified signal
<img src="https://github.com/caraaaaa/template_matching/blob/master/images/Result.jpg" width="50%" height="50%">
