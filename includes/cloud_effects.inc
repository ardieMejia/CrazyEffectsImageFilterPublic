<?php

class cloudBehaviour{
    public $cloudWeight;
    public $cloudDispersion;
    private $initialRGB=array(253,253,255);

    function __construct($cloudWeight,$cloudDispersion){

        $this->cloudWeight=$cloudWeight;
        $this->cloudDispersion=$cloudDispersion;

    }
    function getRGB_array(){

        $red=$this->initialRGB[0];$green=$this->initialRGB[1];$blue=$this->initialRGB[2];
//        echo gettype($this->cloudWeight);
        $red=$red-($this->cloudWeight*25*($this->cloudWeight/8));
        $green=$green-($this->cloudWeight*25*($this->cloudWeight/8));
        $blue=$blue-($this->cloudWeight*25*($this->cloudWeight/8));

        return array((int)$red,(int)$green,(int)$blue);
    }
}

function addPuffs($res,$cloudCenterX,$cloudCenterY,$size,$cloudDiameter,$cloudObject){


    $cloudRGB_array=$cloudObject->getRGB_array();
    $cloudDispersion=$cloudObject->cloudDispersion;

    $puffPct=rand(20,75)/100;
    $puffDiameter=array($cloudDiameter[0]*$puffPct,$cloudDiameter[1]*$puffPct);

    $canvas=imagecreatetruecolor($puffDiameter[0],$puffDiameter[1]);

    $black=imagecolorallocate($canvas,0,0,0);
    imagecolortransparent($canvas,$black);


    $targetY=$cloudCenterY+$cloudDiameter[1]/2-$puffDiameter[1];

    $randPct=rand(-70,70)/100;
    // the bigger difference between puff and main cloud "body" the bigger the dispersion
    $modifier_diff=$cloudDispersion/8*2.0;
    $modifier_diff=1.2+$modifier_diff;
    $puffDiff=$modifier_diff*($cloudDiameter[0]-$puffDiameter[0]);
    $targetX=$cloudCenterX+$puffDiff*$randPct;

    
    //-------- cloud shadow --------
    //    $shadowcolor=imagecolorallocate($canvas,150, 150, 150);
    //imagefilledellipse($canvas,$puffDiameter[0]/2,$puffDiameter[1]/2,$puffDiameter[0],$puffDiameter[1],$shadowcolor);
    //imagecopymerge($res,$canvas,$targetX,$targetY+4,0,0,$cloudDiameter[0],$cloudDiameter[1],60);
    //-------- cloud shadow --------

    $ellipsecolor=imagecolorallocate($canvas,$cloudRGB_array[0],$cloudRGB_array[1],$cloudRGB_array[2]);
    imagefilledellipse($canvas,$puffDiameter[0]/2,$puffDiameter[1]/2,$puffDiameter[0],$puffDiameter[1],$ellipsecolor);
    imagecopymerge($res,$canvas,$targetX,$targetY,0,0,$cloudDiameter[0],$cloudDiameter[1],50);
    imagecopymerge($res,$canvas,$targetX+$targetX/60,$targetY+$targetY/60,0,0,$cloudDiameter[0],$cloudDiameter[1],50);
}

// other possible shades of blue 0,191,255
function oneCloud($res,$cloudCenterX,$cloudCenterY,$size,$cloudDiameter,$cloudObject){

    

    // I call it canvas, because like Photoshop, u need a canvas before you can do anything
    $canvas=imagecreatetruecolor($cloudDiameter[0],$cloudDiameter[1]);
    $black=imagecolorallocate($canvas,0,0,0);
    imagecolortransparent($canvas,$black);


    $cloudRGB_array=$cloudObject->getRGB_array();


    // random number of calls to add puffiness to cloud
    $maxPuff=rand(4,7);
    for($i=0;$i<$maxPuff;$i++){
        addPuffs($res,$cloudCenterX,$cloudCenterY,$size,$cloudDiameter,$cloudObject);
    }

    //-------- cloud shadow --------
    //$shadecolor=imagecolorallocate($canvas,200,200,200);
    //imagefilledellipse($canvas,$cloudDiameter[0]/2,$cloudDiameter[1]/2,$cloudDiameter[0],$cloudDiameter[1],$shadecolor);
    //imagecopymerge($res,$canvas,$cloudCenterX-($cloudDiameter[0]/2),$cloudCenterY-($cloudDiameter[1]/2)+4,0,0,$cloudDiameter[0],$cloudDiameter[1],60);
    //-------- cloud shadow --------

    $ellipsecolor=imagecolorallocate($canvas,$cloudRGB_array[0],$cloudRGB_array[1],$cloudRGB_array[2]);
    imagefilledellipse($canvas,$cloudDiameter[0]/2,$cloudDiameter[1]/2,$cloudDiameter[0],$cloudDiameter[1],$ellipsecolor);
    imagecopymerge($res,$canvas,$cloudCenterX-($cloudDiameter[0]/2),$cloudCenterY-($cloudDiameter[1]/2),0,0,$cloudDiameter[0],$cloudDiameter[1],50);


    $ellipsecolor=imagecolorallocate($canvas,$cloudRGB_array[0],$cloudRGB_array[1],$cloudRGB_array[2]);
    imagefilledellipse($canvas,$cloudDiameter[0]/2,$cloudDiameter[1]/2,$cloudDiameter[0],$cloudDiameter[1],$ellipsecolor);
    imagecopymerge($res,$canvas,$cloudCenterX+$cloudCenterX/50-($cloudDiameter[0]/2),$cloudCenterY+$cloudCenterY/50-($cloudDiameter[1]/2),0,0,$cloudDiameter[0],$cloudDiameter[1],50);





    // random number of calls to add puffiness to cloud
    $maxPuff=rand(4,7);
    for($i=0;$i<$maxPuff;$i++){
        addPuffs($res,$cloudCenterX,$cloudCenterY,$size,$cloudDiameter,$cloudObject);
    }

}

function randomCloudPlacement($res,$size,$cloudDiameter,$cloudObject){

    $cloudWeight=$cloudObject->cloudWeight;

    $cloudCenterX=$size[0]/2+mt_rand(-1*$size[0]/2,$size[0]/2);
    $cloudCenterY=intval(floatval($size[1])*1/8);

    // max=mt_rand(1,4);
    //cloudweight/8*100
    $oneBodyMax=abs($cloudWeight-6)+1;
    $oneBodyOffset=$cloudWeight/8*$cloudCenterX/20;



    for($i=0;$i<$oneBodyMax;$i++){
        $oneBodyOffset=mt_rand(2,9)/10*$oneBodyOffset;
        oneCloud($res,$cloudCenterX+$oneBodyOffset,$cloudCenterY+$oneBodyOffset,$size,$cloudDiameter,$cloudObject);
    }

}

?>
