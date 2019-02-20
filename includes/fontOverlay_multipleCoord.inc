<?php

include './includes/generatorFunctions.inc';



function multiple_addCircle($res,$fontSize,$coordinatesArray,$numberOfSteps){
    $someColorObject=new gradientObject;
    $randomColor=randomColorGenerator($res,$someColorObject);

    // --------------- all this code does is create random hue from raw RGB value and make sure there is "some" Hue, rather than grayscale---------------
    $red2=$someColorObject->destinationRed;
    $green2=$someColorObject->destinationGreen;
    $blue2=$someColorObject->destinationBlue;

    $red1=$someColorObject->sourceRed;
    $green1=$someColorObject->sourceGreen;
    $blue1=$someColorObject->sourceBlue;

    $stepRed=$someColorObject->stepRed;
    $stepGreen=$someColorObject->stepGreen;
    $stepBlue=$someColorObject->stepBlue;
    if($someColorObject->sourceRed<0){
        $red1=mt_rand(0,255);$green1=mt_rand(0,255);$blue1=mt_rand(0,255);
        $arrayRGB=array($red1,$green1,$blue1);
        $maxRGB=max($arrayRGB);
        $minRGB=min($arrayRGB);
        $diffRGB=$maxRGB-$minRGB;
        $hue1=getHuePct(array($red1,$green1,$blue1));
        $hue2=getHuePct(array($red2,$green2,$blue2));
        $diffEachHue=$hue1-$hue2;



        // loop ensures that there is "some" Hue , not grayscale
        // plus: theres difference between each both's R's, Gs and B's
        while($diffRGB<200 && $diffEachHue<50){

            $red2=mt_rand(0,255);$green2=mt_rand(0,255);$blue2=mt_rand(0,255);
            $arrayRGB=array($red2,$green2,$blue2);
            $maxRGB=max($arrayRGB);
            $minRGB=min($arrayRGB);
            $diffRGB=$maxRGB-$minRGB;
            $hue1=getHuePct(array($red1,$green1,$blue1));
            $hue2=getHuePct(array($red2,$green2,$blue2));
            $diffEachHue=$hue1-$hue2;

        }

        $someColorObject->sourceRed=$red1;
        $someColorObject->sourceGreen=$green1;
        $someColorObject->sourceBlue=$blue1;

        $stepRed=(int)(($red1-$red2)/$numberOfSteps);
        $stepGreen=(int)(($green1-$green2)/$numberOfSteps);
        $stepBlue=(int)(($blue1-$blue2)/$numberOfSteps);

        $someColorObject->stepRed=$stepRed;
        $someColorObject->stepGreen=$stepGreen;
        $someColorObject->stepBlue=$stepBlue;

    }
    // --------------- all this code does is create random hue from raw RGB value and make there is "some" Hue, rather than grayscale---------------


    $circleDiameter[0]=(int)(200/100*$fontSize);
    $circleDiameter[1]=(int)(200/100*$fontSize);

    for($i=0;$i<sizeof($coordinatesArray);$i++){



        $someColorObject->sourceRed=$someColorObject->sourceRed-$someColorObject->stepRed;
        $someColorObject->sourceGreen=$someColorObject->sourceGreen-$someColorObject->stepGreen;
        $someColorObject->sourceBlue=$someColorObject->sourceBlue-$someColorObject->stepBlue;


        if($someColorObject->sourceRed>255)$someColorObject->sourceRed=255;
        if($someColorObject->sourceGreen>255)$someColorObject->sourceGreen=255;
        if($someColorObject->sourceBlue>255)$someColorObject->sourceBlue=255;
        if($someColorObject->sourceRed<0)$someColorObject->sourceRed=0;
        if($someColorObject->sourceGreen<0)$someColorObject->sourceGreen=0;
        if($someColorObject->sourceBlue<0)$someColorObject->sourceBlue=0;



        $canvas=imagecreatetruecolor($circleDiameter[0],$circleDiameter[1]);
        $black=imagecolorallocate($canvas,0,0,0);
        imagecolortransparent($canvas,$black); // note to self: strange that transparent background needs a "color object" to bahve properly, 
        $circleColor=imagecolorallocate($canvas,$someColorObject->sourceRed, $someColorObject->sourceGreen, $someColorObject->sourceBlue);
        imagefilledellipse($canvas,$circleDiameter[0]/2,$circleDiameter[1]/2,$circleDiameter[0],$circleDiameter[1],$circleColor);
        imagecopymerge($res,$canvas,$coordinatesArray[$i]['x']-$circleDiameter[0]/2,$coordinatesArray[$i]['y']-$circleDiameter[0]/2,0,0,$circleDiameter[0],$circleDiameter[1],100);



    }

}

function circlesGradient_basic($res,$fontSize,$fontX,$fontY,$coordinatesArray,$fontFile,$fontString){


    multiple_addCircle($res,$fontSize,$coordinatesArray,sizeof($coordinatesArray));
    $fontColor=imagecolorallocate($res,255,255,255);
    imagettftext($res,$fontSize,0,$fontX,$fontY+$fontSize/2,$fontColor,$fontFile,$fontString);
}

?>
