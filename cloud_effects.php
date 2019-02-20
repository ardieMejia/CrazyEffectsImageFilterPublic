<?php



include "./includes/cloud_effects.inc";

$fileString='./src-img/clouds/'.$photoSelectedOne;

$size=getimagesize($fileString);



$res=imagecreatefromjpeg($fileString);




function create_a_cloud($res,$size,$cloudWeight,$cloudDispersion){
    $cloudObject=new cloudBehaviour($cloudWeight,$cloudDispersion);
    $cloudNumbers=rand(1,2);
    $p_cloudDiameter=$cloudWeight/8*0.1;
    $p_cloudDiameter=0.1+$p_cloudDiameter;
    for($i=0;$i<$cloudNumbers;$i++){
        $cloudDiameter=array($size[0]*$p_cloudDiameter,$size[0]*$p_cloudDiameter);
        randomCloudPlacement($res,$size,$cloudDiameter,$cloudObject);
    }
}



create_a_cloud($res,$size,$cloudWeight,$cloudDispersion);



// output the picture
header("Content-type: image/png");
imagepng($res);

?>




