<?php
include './includes/fontOverlay.inc';



if(isset($_GET['photoSelectedOne'])){
    $photoSelectedOne=$_GET['photoSelectedOne'];
    $fontString=$_GET['fontString'];
    $fontX=$_GET['fontOverImage_x'];
    $fontY=$_GET['fontOverImage_y'];
    $fontSelected=$_GET['fontSelected'];
    $effectsChosen=$_GET['effectsChosen'];
}

else
    die("photoSelectedOne from GET has dissapeared into another dimension");

switch (strlen($fontString)){
    case 0:
        include './includes/nicerWarning.inc';
        exit;
    default:
        break;
}


$res=imagecreatefromjpeg("./src-img/tableDisplay/".$photoSelectedOne);
$fontFile="./src-misc/".$fontSelected;
//$fontString="NPC's everywhere";

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


switch ($effectsChosen){
    case "fontOverlaySingle":
        fontOverlaySingle($res,$fontSize,$fontX,$fontY,$fontFile,$fontString);
        break;
    case "fontOverlayShade":
        fontOverlayShade($res,$fontSize,$fontX,$fontY,$fontFile,$fontString);
        break;
    case "fontOverlayShadeTransparent":
        fontOverlayShadeTransparent($res,$fontSize,$fontX,$fontY,$fontFile,$fontString);
        break;
    case "fontContrastColor_basic":
        fontContrastColor_basic($res,$fontSize,$fontX,$fontY,$fontFile,$fontString,$fontBoxDetails);
        break;
    case "fontContrastColor_hue":
        fontContrastColor_hue($res,$fontSize,$fontX,$fontY,$fontFile,$fontString,$fontBoxDetails);
        break;
    case "contrastWatermark":
        contrastWatermark($res,$fontSize,$fontX,$fontY,$fontFile,$fontString,$fontBoxDetails,$imageSize);
        break;
    case "randomFontOverlay":
        randomFontOverlay($res,$fontSize,$fontX,$fontY,$fontFile,$fontString,$filesInFontArray=scandir("./src-misc/"));
        break;
    case "randomFontOverlayWithRandomGradient":
        randomFontOverlayWithRandomGradient($res,$fontSize,$fontX,$fontY,$fontFile,$fontString,$filesInFontArray=scandir("./src-misc/"),$imageSize);
        break;
    case "fontOverlaySingleRandomColor":
        fontOverlaySingleRandomColor($res,$fontSize,$fontX,$fontY,$fontFile,$fontString);
        break;
    case "fontOverlayMultipleShade":
        fontOverlayMultipleShade($res,$fontSize,$fontX,$fontY,$fontFile,$fontString);
        break;
    case "fontOverlay3D_primaryColor":
        fontOverlay3D_primaryColor($res,$fontSize,$fontX,$fontY,$fontFile,$fontString,$imageSize);
        break;
    case "fontOverlay_secondaryColor":
        fontOverlay_secondaryColor($res,$fontSize,$fontX,$fontY,$fontFile,$fontString,$imageSize);
        break;
    default:
        break;
}









header("Content-Type: image/jpeg");
imagejpeg($res);

?>


