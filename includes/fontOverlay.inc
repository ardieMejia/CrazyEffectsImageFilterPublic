<?php

include 'generatorFunctions.inc';

function fontOverlaySingle($res,$fontSize,$fontX,$fontY,$fontFile,$fontString){
    $fontColor=imagecolorallocate($res,255,255,255);
    imagettftext($res,$fontSize,0,$fontX,$fontY,$fontColor,$fontFile,$fontString);
}

function fontOverlayShade($res,$fontSize,$fontX,$fontY,$fontFile,$fontString){
    $fontColor=imagecolorallocate($res,255,255,255);
    $shadeColor=imagecolorallocate($res,150,150,150);
    imagettftext($res,$fontSize,0,$fontX+4,$fontY+2,$shadeColor,$fontFile,$fontString);
    imagettftext($res,$fontSize,0,$fontX,$fontY,$fontColor,$fontFile,$fontString);
}

function fontOverlayShadeTransparent($res,$fontSize,$fontX,$fontY,$fontFile,$fontString){
    $fontColor=imagecolorallocate($res,255,255,255);
    $shadeColor=imagecolorallocatealpha($res,150,150,150,50);
    imagettftext($res,$fontSize,0,$fontX+4,$fontY+2,$shadeColor,$fontFile,$fontString);
    imagettftext($res,$fontSize,0,$fontX,$fontY,$fontColor,$fontFile,$fontString);
}

function fontOverlaySingleRandomColor($res,$fontSize,$fontX,$fontY,$fontFile,$fontString){

    // slight misnomer/misnaming of gradientObject here, gradientObject used only for single color
    $ColorObject=new gradientObject;

    $fontColor=randomColorGenerator($res,$ColorObject);
    imagettftext($res,$fontSize,0,$fontX,$fontY,$fontColor,$fontFile,$fontString);
}

function fontOverlayMultipleShade($res,$fontSize,$fontX,$fontY,$fontFile,$fontString){

    $fontColor=imagecolorallocate($res,255,255,255);

    // determine length of shadow based on fontSize
    // set color of shadowBaseColor
    // set deLimiter
    $shadeBaseArray=array(180,180,180,50);
    $shadowNumbers=(int)($fontSize/3);
    if($shadowNumbers<2);$shadowNumbers+3;
    $Xoffset=mt_rand(-1,1);
    $Yoffset=mt_rand(-1,1);

    for ($i=0;$i<$shadowNumbers;$i++){
        singleTextShade($res,$fontSize,$fontX+$Xoffset*$i,$fontY+$Yoffset*$i,$shadeBaseArray,$fontFile,$fontString);
    }
    imagettftext($res,$fontSize,0,$fontX,$fontY,$fontColor,$fontFile,$fontString);

}


function fontOverlay3D_primaryColor($res,$fontSize,$fontX,$fontY,$fontFile,$fontString,$imageSize){

    $colorArray=getAverageHue($res,$imageSize);


    $fontColor=imagecolorallocate($res,$colorArray[0],$colorArray[1],$colorArray[2]);


    // determine length of shadow based on fontSize
    // set color of shadowBaseColor
    // set deLimiter


    //$shadeBaseArray=array(180,180,180,50);
    $shadeBaseArray=nudgeItDark($colorArray);
    array_push($shadeBaseArray,50);


    $shadowNumbers=(int)($fontSize/3);
    if($shadowNumbers<2);$shadowNumbers+3;
    $Xoffset=mt_rand(-1,1);
    $Yoffset=mt_rand(-1,1);

    for ($i=0;$i<$shadowNumbers;$i++){
        singleTextShade($res,$fontSize,$fontX+$Xoffset*$i,$fontY+$Yoffset*$i,$shadeBaseArray,$fontFile,$fontString);
    }
    imagettftext($res,$fontSize,0,$fontX,$fontY,$fontColor,$fontFile,$fontString);

}


function randomFontOverlay($res,$fontSize,$fontX,$fontY,$fontFile,$fontString,$filesInFontArray){
    $fontColor=imagecolorallocate($res,255,255,255);

    $uniqueFontArray=[];

    foreach ($filesInFontArray as $files){

        if(preg_match('/(ttf)/',$files)){
            if(!preg_match('/('.$patternPrev.')/',$files)){
                array_push($uniqueFontArray,$files);
            }
        }
        $patternPrev=substr($files,0,4);
    }

    $fontStringArray=str_split($fontString);
    $fontSize-=6;


    //    for ($i=0;$i<sizeof($fontString);$i++){

    foreach ($fontStringArray as $fontCharacter){
        $randomAngle=mt_rand(-30,30);
        $fontFile="./src-misc/".strval($uniqueFontArray[mt_rand(0,sizeof($uniqueFontArray)-1)]);

        $fontBoxDetails=imageftbbox($fontSize,0,$fontFile,$fontCharacter);
        $nextOffset=$fontBoxDetails[2]-$fontBoxDetails[0];

        $fontX+=$nextOffset+4;

        imagettftext($res,$fontSize,$randomAngle,$fontX,$fontY,$fontColor,$fontFile,$fontCharacter);


    }

}


function fontContrastColor_basic($res,$fontSize,$fontX,$fontY,$fontFile,$fontString,$fontBoxDetails){

    $calcBoxArray=array('x'=>$fontX,'y'=>$fontY-$fontSize,'width'=>($fontBoxDetails[2]-$fontBoxDetails[0]),'height'=>($fontBoxDetails[3]-$fontBoxDetails[5]));



    $calcRes=imagecrop($res,$calcBoxArray);
    imagefilter($calcRes,IMG_FILTER_NEGATE);
    $redAvg=0;$greenAvg=0;$blueAvg=0;

    for($i=0;$i<imagesx($calcRes);$i++){
        for($j=0;$j<imagesy($calcRes);$j++){
            $colorIndex=imagecolorat($calcRes,$i,$j);
            $colorArray=imagecolorsforindex($calcRes,$colorIndex);
            $redAvg+=$colorArray['red'];
            $greenAvg+=$colorArray['green'];
            $blueAvg+=$colorArray['blue'];
        }
    }
    $redAvg=(int)($redAvg/imagesx($calcRes)/imagesy($calcRes));
    $greenAvg=(int)($greenAvg/imagesx($calcRes)/imagesy($calcRes));
    $blueAvg=(int)($blueAvg/imagesx($calcRes)/imagesy($calcRes));


    $fontColor=imagecolorallocate($res,$redAvg,$greenAvg,$blueAvg);
    imagettftext($res,$fontSize,0,$fontX,$fontY,$fontColor,$fontFile,$fontString);

}

function fontContrastColor_hue($res,$fontSize,$fontX,$fontY,$fontFile,$fontString,$fontBoxDetails){
    $calcBoxArray=array('x'=>$fontX,'y'=>$fontY-$fontSize,'width'=>($fontBoxDetails[2]-$fontBoxDetails[0]),'height'=>($fontBoxDetails[3]-$fontBoxDetails[5]));
    $calcRes=imagecrop($res,$calcBoxArray);

    imagefilter($calcRes,IMG_FILTER_NEGATE);
    //    imagefilter($calcRes,IMG_FILTER_CONTRAST,-90);

    $redAvg=0;$greenAvg=0;$blueAvg=0;

    $colorIndex=imagecolorat($calcRes,0,0);
    $colorArray=imagecolorsforindex($calcRes,$colorIndex);
    $redPrev=$colorArray['red'];
    $greenPrev=$colorArray['green'];
    $bluePrev=$colorArray['blue'];

    for($i=0;$i<imagesx($calcRes);$i++){
        for($j=0;$j<imagesy($calcRes);$j++){
            if($i!=0&&$j!=0){

                $colorIndex=imagecolorat($calcRes,$i,$j);
                $colorArray=imagecolorsforindex($calcRes,$colorIndex);
                if(max($colorArray)-min($colorArray)>30){
                    $redPrev=($colorArray['red']+$redPrev)/2;
                    $greenPrev=($colorArray['green']+$greenPrev)/2;
                    $bluePrev=($colorArray['blue']+$bluePrev)/2;

                }
            }

        }
    }

    $fontColor=imagecolorallocate($res,$redPrev,$greenPrev,$bluePrev);
    imagettftext($res,$fontSize,0,$fontX,$fontY,$fontColor,$fontFile,$fontString);

}

// contrastWatermark code borrowed from fontContrastColor_hue()
function contrastWatermark($res,$fontSize,$fontX,$fontY,$fontFile,$fontString,$fontBoxDetails,$imageSize){
    $calcBoxArray=array('x'=>$fontX,'y'=>$fontY-$fontSize,'width'=>($fontBoxDetails[2]-$fontBoxDetails[0]),'height'=>($fontBoxDetails[3]-$fontBoxDetails[5]));
    $calcRes=imagecrop($res,$calcBoxArray);

    imagefilter($calcRes,IMG_FILTER_NEGATE);
    //    imagefilter($calcRes,IMG_FILTER_CONTRAST,-90);

    $redAvg=0;$greenAvg=0;$blueAvg=0;

    $colorIndex=imagecolorat($calcRes,0,0);
    $colorArray=imagecolorsforindex($calcRes,$colorIndex);
    $redPrev=$colorArray['red'];
    $greenPrev=$colorArray['green'];
    $bluePrev=$colorArray['blue'];

    for($i=0;$i<imagesx($calcRes);$i++){
        for($j=0;$j<imagesy($calcRes);$j++){
            if($i!=0&&$i!=0){

                $colorIndex=imagecolorat($calcRes,$i,$j);
                $colorArray=imagecolorsforindex($calcRes,$colorIndex);
                if(max($colorArray)-min($colorArray)>30){
                    $redPrev=($colorArray['red']+$redPrev)/2;
                    $greenPrev=($colorArray['green']+$greenPrev)/2;
                    $bluePrev=($colorArray['blue']+$bluePrev)/2;

                }
            }

        }
    }


    imagealphablending($res,true);
    $fontColor=imagecolorallocatealpha($res,$redPrev,$greenPrev,$bluePrev,50);
    imagettftext($res,$fontSize,0,$fontX,$fontY,$fontColor,$fontFile,$fontString);

}


function randomFontOverlayWithRandomGradient($res,$fontSize,$fontX,$fontY,$fontFile,$fontString,$filesInFontArray,$imageSize){



    $firstColorObject=new gradientObject;

    $uniqueFontArray=[];



    $randomColor=randomColorGenerator($res,$firstColorObject);



    foreach ($filesInFontArray as $files){

        if(preg_match('/(ttf)/',$files)){
            if(!preg_match('/('.$patternPrev.')/',$files)){
                array_push($uniqueFontArray,$files);
            }
        }
        $patternPrev=substr($files,0,4);
    }

    $fontStringArray=str_split($fontString);
    $fontSize-=6;


    foreach ($fontStringArray as $fontCharacter){
        $randomAngle=mt_rand(-30,30);
        $fontFile="./src-misc/".strval($uniqueFontArray[mt_rand(0,sizeof($uniqueFontArray)-1)]);

        $fontBoxDetails=imageftbbox($fontSize,0,$fontFile,$fontCharacter);
        $nextOffset=$fontBoxDetails[2]-$fontBoxDetails[0];

        $fontX+=$nextOffset+4;

        imagettftext($res,$fontSize,$randomAngle,$fontX,$fontY,$randomColor,$fontFile,$fontCharacter);



        $randomColor=randomNextGradient($res,$firstColorObject,sizeof($fontStringArray));


    }


}

function fontOverlay_secondaryColor($res,$fontSize,$fontX,$fontY,$fontFile,$fontString,$imageSize){


    //    print_r($colorArray);

    $colorArray=getSecondaryHue($res,$imageSize);
    //    print_r($colorArray);

    $fontColor=imagecolorallocate($res,$colorArray[0],$colorArray[1],$colorArray[2]);
    $shade=imagecolorallocate($res,10,10,10);

    imagettftext($res,15,0,$fontX+2,$fontY+2,$shade,$fontFile,"secondary"); // shadow
    imagettftext($res,15,0,$fontX,$fontY,$fontColor,$fontFile,"secondary");
    imagettftext($res,$fontSize,0,$fontX+2+120,$fontY+2,$shade,$fontFile,$fontString); // shadow
    imagettftext($res,$fontSize,0,$fontX+120,$fontY,$fontColor,$fontFile,$fontString);


    $colorArray=getAverageHue($res,$imageSize);
    $fontColor=imagecolorallocate($res,$colorArray[0],$colorArray[1],$colorArray[2]);
    imagettftext($res,15,0,$fontX+2,$fontY+50+2,$shade,$fontFile,"primary");
    imagettftext($res,15,0,$fontX,$fontY+50,$fontColor,$fontFile,"primary");
    imagettftext($res,$fontSize,0,$fontX+2+120,$fontY+50+2,$shade,$fontFile,$fontString);
    imagettftext($res,$fontSize,0,$fontX+120,$fontY+50,$fontColor,$fontFile,$fontString);

}


?>


