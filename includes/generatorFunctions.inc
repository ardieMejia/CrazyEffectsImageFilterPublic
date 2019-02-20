<?php

// ------------------------------
// things to do to improve code...

// our singleTextShade uses an color object/identifier, hence does not RGB array as argument
// nudgeItDark has to return array, because it only nudges

// ok, ok, wait. While, color objects are "neater" to return, arrays are more useful, since that
// we can still play around with the values...

// However, if we are serious about improving code, simply create another project...
// and read about PHP's ability to get RGB array from color object/identifier..
// and then REWRITE ENTIRE PROJECT
// ------------------------------

class gradientObject{
    public $destinationRed=-1;
    public $destinationGreen=-1;
    public $destinationBlue=-1;

    public $stepRed=0;
    public $stepGreen=0;
    public $stepBlue=0;

    public $sourceRed=-1;
    public $sourceGreen=-1;
    public $sourceBlue=-1;

}

// ------------ again, not exactly Hue value, but it works
function getHuePct($colorArray){

    $hueAvg=0;
    $hue=$colorArray[0]/255+$colorArray[1]/255*2+$colorArray[2]/255*4;

    return $hue/7*100;

}

function nudgeItDark($colorArray){
    if($colorArray[0]>29)$colorArray[0]-=30;
    if($colorArray[1]>29)$colorArray[1]-=30;
    if($colorArray[2]>29)$colorArray[2]-=30;

    return $colorArray;

}

function isItLightNotDark($colorArray){
    $redPct=$colorArray[0]/255*100;
    $greenPct=$colorArray[1]/255*100;
    $bluePct=$colorArray[2]/255*100;

    $avgPct=($redPct+$greenPct+$bluePct)/3;

    if($avgPct>50)
        return true;
    elseif($avgPct<50)
        return false;
}


function randomColorGenerator($res,$randomGradientObject){

    $red1=mt_rand(0,255);$green1=mt_rand(0,255);$blue1=mt_rand(0,255);
    $arrayRGB=array($red1,$green1,$blue1);
    $maxRGB=max($arrayRGB);
    $minRGB=min($arrayRGB);
    $diffRGB=$maxRGB-$minRGB;
    // loop ensures that there is "some" Hue , not grayscale
    while($diffRGB<100){

        $red1=mt_rand(0,255);$green1=mt_rand(0,255);$blue1=mt_rand(0,255);
        $arrayRGB=array($red1,$green1,$blue1);
        $maxRGB=max($arrayRGB);
        $minRGB=min($arrayRGB);
        $diffRGB=$maxRGB-$minRGB;
    }
    $randomGradientObject->destinationRed=$red1;
    $randomGradientObject->destinationGreen=$green1;
    $randomGradientObject->destinationBlue=$blue1;

    return imagecolorallocate($res,$red1,$green1,$blue1);

}

function singleTextShade($res,$fontSize,$fontX,$fontY,$shadeBaseArray,$fontFile,$fontString){

    $shadeColor=imagecolorallocatealpha($res,$shadeBaseArray[0],$shadeBaseArray[1],$shadeBaseArray[2],$shadeBaseArray[3]);
    imagettftext($res,$fontSize,0,$fontX,$fontY,$shadeColor,$fontFile,$fontString);
}

// not exact Hue calculation, but works on the same principle of "color space"
function getAverageHue($res,$imageSize){

    $hueAvg=0;
    for($i=0;$i<$imageSize[0];$i++){
        for($j=0;$j<$imageSize[1];$j++){

            $colorIndex=imagecolorat($res,$i,$j);
            $colorArray=imagecolorsforindex($res,$colorIndex);
            $hue=$colorArray['red']+$colorArray['green']*1000+$colorArray['blue']*1000000;
            $hueAvg+=$hue;
        }
    }
    $hueAvg=(int)($hueAvg/($i+1)/($j+1));


    $avgCounter=0;$red=0;$green=0;$blue=0;

    for($i=0;$i<$imageSize[0];$i++){
        for($j=0;$j<$imageSize[1];$j++){

            $colorIndex=imagecolorat($res,$i,$j);
            $colorArray=imagecolorsforindex($res,$colorIndex);
            $hue=$colorArray['red']+$colorArray['green']*1000+$colorArray['blue']*1000000;
            $diffHue=abs($hue-$hueAvg);
            $PctDiff=$diffHue/255255255;
            if($PctDiff<20){
                $red+=$colorArray['red'];$green+=$colorArray['green'];$blue+=$colorArray['blue'];
                $avgCounter++;
            }

        }
    }

    $red=(int)($red/$avgCounter);
    $green=(int)($green/$avgCounter);
    $blue=(int)($blue/$avgCounter);

    // ------------ value checks ------------
    if($red<0)$red=0;if($red>255)$red=255;
    if($green<0)$green=0;if($green>255)$green=255;
    if($blue<0)$blue=0;if($blue>255)$blue=255;
    // ------------ value checks ------------


    return array($red,$green,$blue);


}



function randomNextGradient($res,$firstColorObject,$numberOfSteps){

    $red1=$firstColorObject->destinationRed;
    $green1=$firstColorObject->destinationGreen;
    $blue1=$firstColorObject->destinationBlue;

    $red2=$firstColorObject->sourceRed;
    $green2=$firstColorObject->sourceGreen;
    $blue2=$firstColorObject->sourceBlue;

    $stepRed=$firstColorObject->stepRed;
    $stepGreen=$firstColorObject->stepGreen;
    $stepBlue=$firstColorObject->stepBlue;

    // if source* Colors is not defined, 
    if($firstColorObject->sourceRed<0){
        $red2=mt_rand(0,255);$green2=mt_rand(0,255);$blue2=mt_rand(0,255);
        $arrayRGB=array($red2,$green2,$blue2);
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

        $firstColorObject->sourceRed=$red2;
        $firstColorObject->sourceGreen=$green2;
        $firstColorObject->sourceBlue=$blue2;

        $stepRed=(int)(($red1-$red2)/$numberOfSteps);
        $stepGreen=(int)(($green1-$green2)/$numberOfSteps);
        $stepBlue=(int)(($blue1-$blue2)/$numberOfSteps);

        $firstColorObject->stepRed=$stepRed;
        $firstColorObject->stepGreen=$stepGreen;
        $firstColorObject->stepBlue=$stepBlue;

    }

    $maxStep=max($firstColorObject->stepRed,$firstColorObject->stepGreen);
    $maxStep=max($maxStep,$firstColorObject->stepBlue);

    //if($firstColorObject->stepRed==$maxStep)
    $firstColorObject->destinationRed=$firstColorObject->destinationRed-$firstColorObject->stepRed;
    //if($firstColorObject->stepGreen==$maxStep)
    $firstColorObject->destinationGreen=$firstColorObject->destinationGreen-$firstColorObject->stepGreen;
    //if($firstColorObject->stepBlue==$maxStep)
    $firstColorObject->destinationBlue=$firstColorObject->destinationBlue-$firstColorObject->stepBlue;

    if($firstColorObject->destinationRed>255)$firstColorObject->destinationRed=255;
    if($firstColorObject->destinationGreen>255)$firstColorObject->destinationGreen=255;
    if($firstColorObject->destinationBlue>255)$firstColorObject->destinationBlue=255;


    return imagecolorallocate($res,$firstColorObject->destinationRed,$firstColorObject->destinationGreen,$firstColorObject->destinationBlue);

}

function getSecondaryHue($res,$imageSize){

    $averageHueArray=getAverageHue($res,$imageSize);

    $width=(int)($imageSize[0]/32);
    $height=(int)($imageSize[1]/32);
    $redStructureArray=[];$greenStructureArray=[];$blueStructureArray=[];
    for($i=0;$i<32;$i+=$width){
        for($j=0;$j<32;$j+=$height){
            if(($width*32)>$imageSize[0])
                $width=$width-($width*32-$imageSize[0]);
            if(($width*32)>$imageSize[0])
                $height=$height-($height*32-$imageSize[1]);

            $calcBoxArray=array('x'=>$i,'y'=>$j,'width'=>$width,'height'=>$height);
            $calcRes=imagecrop($res,$calcBoxArray);
            $redAvg=0;$greenAvg=0;$blueAvg=0;
            $avgCounter=0;
            for($k=0;$k<imagesx($calcRes);$k++){
                for($l=0;$l<imagesy($calcRes);$l++){

                    $colorIndex=imagecolorat($calcRes,$k,$l);
                    $colorArray=imagecolorsforindex($calcRes,$colorIndex);
                    if(max($colorArray)-min($colorArray)>70){
                        $redAvg+=$colorArray['red'];
                        $greenAvg+=$colorArray['green'];
                        $blueAvg+=$colorArray['blue'];
                        $avgCounter++;
                    }

                }
            }

            if($avgCounter!=0){
                array_push($redStructureArray,(int)($redAvg/$avgCounter));
                array_push($greenStructureArray,(int)($greenAvg/$avgCounter));
                array_push($blueStructureArray,(int)($blueAvg/$avgCounter));
            }else{ // if no difference in color/hue, just use primary again
                array_push($redStructureArray,$averageHueArray[0]);
                array_push($greenStructureArray,$averageHueArray[1]);
                array_push($blueStructureArray,$averageHueArray[2]);
            }


        }

    }
    $diffArray=[];
    for($i=0;$i<sizeof($redStructureArray);$i++){
        $diffSum=abs($redStructureArray[$i]-$averageHueArray[0])+abs($greenStructureArray[$i]-$averageHueArray[1])+abs($blueStructureArray[$i]-$averageHueArray[2]);
        array_push($diffArray,$diffSum);
    }

    for($i=0;$i<sizeof($redStructureArray);$i++){
        if(max($diffArray)==$diffArray[$i])
            $secondaryRGBArray=array($redStructureArray[$i],$greenStructureArray[$i],$blueStructureArray[$i]);
    }

    return $secondaryRGBArray;



}


?>
