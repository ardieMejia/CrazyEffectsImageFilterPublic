<!DOCTYPE html>
<html lang="en"> 
    <head>
        <meta charset="utf-8"/>
        <link rel="stylesheet" href="./src-css/meme_spectre.css">
        <script src="./src-js/jquery-3.3.1.js"></script>
        <script src="./src-js/jquery.cycle.all.js"></script>

        <style>
         .navfixed{
             background-image:url("./src-img/background/pic_23.jpg");
             background-color:white;
             color:white;
             margin:10px;
             position:fixed;
             top:0;
             right:0;
             float:right;
             display:block;
             width:15%;
         }
         .photoSlideTD{

             table-layout:fixed;
             width:50%;
             float:left;
         }
         .animationTable{
             padding-top:100px;
         }
        </style>
        
    </head>
    <body>
        <header class="bg-primary fixed"><img src="./src-img/icons/output.png" /></header>
        <div class="navfixed">
            <ul>
                You chose the following photos:
                <?php

                
                if(isset($_GET['photoSelected'])){

                    $photoFullString=$_GET['photoSelected'];


                    for($i=0;$i<sizeof($photoFullString);$i++){
                        echo "<li>";

                        echo $photoFullString[$i];
                        echo "</li>";
                    }

                }
                ?>

            </ul>
        </div>
        <div  class="container">

            <table class="animationTable">
                <tr>
                    <th>Animation Table</th>
                </tr>
                <tr>
                    <td id="slideShowInTd" width="50%">


                        <?php
                        
                        
                        if(isset($_GET['photoSelected'])){
                            $photoFullString=$_GET['photoSelected'];
                            for($i=0;$i<sizeof($photoFullString);$i++){
                                echo '<img src="./src-img/effects/'.$photoFullString[$i].'" />';
                            }
                        }
                        

                        ?>
                    </td>
                    <td width="50%">
                        <p>Make a photo app (like your last project), that has a contrast effect, font placement effect (with multiple font choices), another font effect but with dynamic background (depending on the average color of a small area clicked on). But now, think of ways to make it more impressive. Make sure the interface is more pleasant, the font effect with dynamic background should be its own separate function. Perhaps after clicking the photo in the lists, you display a singular photo (this is a single PHP file), with an effect dropdown list, and choosing an effect will trigger an (isset) PHP function to process the photo. This way you can have all those crazy functions inside 1 file. Later we can separate this in an include file. </p>
                       
                    </td>
                </tr>
                
            </table>            

        </div>

        <script>
         $(document).ready(function(){

             $('p:last').append("<strong>added this at document,ready</strong>");

         
                 $('#slideShowInTd').cycle({
                         fx:'zoom',
                                    timeout:'1'
                 });
         

         });
        </script>
    </body>
</html>
