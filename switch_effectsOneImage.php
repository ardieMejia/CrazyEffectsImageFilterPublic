<?php
if(isset($_GET['availableEffects'])){
    $availableEffects=$_GET['availableEffects'];
    $photoSelectedOne=$_GET['photoSelectedOne'];

    switch ($availableEffects){
    case "Clouds":
        include "cloud_effects_interface.php";
        break;
    case "fontOver":
        include "fontOverPosition.php";
                break;
    case "multipleCoordinate":
        include "multipleCoordinate.php";
        break;
    default:

        break;
    }

}


?>


