<?php
include './includes/fontOverlay_multipleCoord.inc';



if(isset($_GET['coordinateArrays'])){
    // chen adding new "feature", add here to pass state
    $photoSelectedOne=$_GET['photoSelectedOne'];

    $coordinateArrays=$_GET['coordinateArrays'];
    // loop throgh coordinateArrays to get minimum of x and y



    $sumOfCoord=[($coordinateArrays[0]+$coordinateArrays[1])/2];



    for($i=2;$i<sizeof($coordinateArrays);$i++){

        if($i%2==1)/* if its even */{
            array_push($sumOfCoord,($coordinateArrays[$i-1]+$coordinateArrays[$i])/2);


        }
    }



    //-----;
    $minValue=99999999;
    for($i=0;$i<sizeof($sumOfCoord);$i++){
        if($sumOfCoord[$i]<$minValue){
            $minIndex=$i;
            $minValue=$sumOfCoord[$i];
        }
    }
    $realMinIndex=$minIndex*2;

    $fontX=$coordinateArrays[$realMinIndex];
    $fontY=$coordinateArrays[$realMinIndex+1];

}
else{
    die("No such thing as coordinateArrays");
}



$res=imagecreatefromjpeg("./src-img/tableDisplay/".$photoSelectedOne);
$fontFile="./src-misc/LiberationSerif-BoldItalic.ttf";
$fontString="NPC's everywhere";

$fontPct=15/100;                // percentage of font depends on image Y
$imageSize=getimagesize("./src-img/tableDisplay/".$photoSelectedOne);
$fontSize=(int)($fontPct*$imageSize[1]);
//minimize just enough, if too large
$fontBoxDetails=imageftbbox($fontSize,0,$fontFile,$fontString);
$fontBox_xMin=$fontBoxDetails[0];$fontBox_xMax=$fontBoxDetails[2];
$overFlow=$fontBox_xMax+$fontX-$imageSize[0];

while($overFlow>0 && $fontSize>1){

    $fontSize--;

    $fontBoxDetails=imageftbbox($fontSize,0,$fontFile,$fontString);
    $fontBox_xMax=$fontBoxDetails[2];
    $overFlow=$fontBox_xMax+$fontX-$imageSize[0];
}

// restructure array..
$tempArray=array(array('x'=>$coordinateArrays[0],'y'=>$coordinateArrays[1]));
for($i=2;$i<sizeof($coordinateArrays);$i++){
    if($i%2!=0)/* if its even */{
        array_push($tempArray,array('x'=>$coordinateArrays[$i-1],'y'=>$coordinateArrays[$i]));
    }
}
$coordinateArrays=$tempArray;



circlesGradient_basic($res,$fontSize,$fontX,$fontY,$coordinateArrays,$fontFile,$fontString);

header("Content-Type: image/jpeg");
imagejpeg($res);

?>


