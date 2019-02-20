<?php
if(isset($_GET['availableEffects'])){
    $availableEffects=$_GET['availableEffects'];
    $photoSelectedOne=$_GET['photoSelectedOne'];
    $fileString="./src-img/tableDisplay/".$photoSelectedOne;

}
?>

<!DOCTYPE html>
<html lang="fa">
    <head>
        <meta charset="utf-8"/>
        <link rel="stylesheet" href="src-css/skeleton.css">
        <script src="./src-js/jquery-3.3.1.js"></script>
        <style>


        </style>

    </head>
    <body>
        <div class="container">

            <h1>Cloud parameters</h1>


            <table>
                <tr>
                    <td width="70%">


                        <img src="<?php
                                  echo $fileString;
                                  ?>" />
                        <h3>.JPEG</h3>
                        
                        nasty tables yet again, nasty tables yet again,
                        nasty tables yet again, nasty tables yet again,
                        nasty tables yet again, nasty tables yet again,
                        nasty tables yet again, nasty tables yet again, 
                        first column at 70%
                        <p>nasty tables yet again, nasty tables yet again, nasty tables yet again, nasty tables yet again, nasty tables yet again, nasty tables yet again, nasty tables yet again, nasty tables yet again, nasty tables yet again</p>
                    </td>
                    <td width="30%">
                        <form method="get" action="./switch_cloudEffects.php">
                            <label>Cloud weight</label>
                            <input name="cloudWeight" type="range" min="1" max="8"/>
                            <label>Cloud dispersion</label>
                            <input name="cloudDispersion"  type="range" min="1" max="8"/>
                            <input hidden name="photoSelectedOne" value="<?php
                                                                         echo $photoSelectedOne;
                                                                         ?>" />
                            <input type="submit" class="button button-active" value="process effects (PHP)"  id="oneEffectOnly"/>
                        </form>
                    </td>
                </tr>
            </table>

        </div>
    </body>
</html>

