<html>
<body style = "background-image: url('addGame.png'); background-repeat: no-repeat; background-size: cover; background-attachment: fixed;"> 
<h3 style = "font-family: Impact; font-size:60px; background-color:#0000ff; text-align:center; color:#ffffff;">Enter information about a Game to add to the database:</h3>

<div align = "center">
    
    <!-- <table>
    <thead> 
    <tr>
        <th>Option</th>
        <th>Function</th>
    </tr>
    </thead>
    <tbody>
    <tr>
        <td>1</td>
        <td>Add new Game </td>
    </tr>
    <tr>
        <td>2</td>
        <td>Add Player</td>
    </tr>
    <tr>
        <td>4</td>
        <td>Boba Guys</td>
    </tr>
    <tr>
        <td>8</td>
        <td>Kung Fu Tea</td>
    </tr>
    <tr>
        <td>15</td>
        <td>Fat Straws</td>
    </tr>
    </tbody>
    </table> -->
</div>

<form align = "center" style = "background-color:#00ffff" action="addGame.php" method="post">
    Team 1 ID: <input type="text" name="TeamID1"><br>
    Team 2 ID: <input type="text" name="TeamID2"><br>
    Team 1 Score: <input type="text" name="Score1"><br>
    Team 2 Score: <input type="text" name="Score2"><br>
    Date: <input type="date" name="Date"><br>
    <b><a href = "hello.php"><input type = "button" value = "Back" style = "background-color:white; border: solid 3px #6e6e6e; height: 30px; vertical-align: 9px"/></a></b>
    <input name="submit" type="submit" style = "background-color:green; border: solid 3px #6e6e6e; height: 30px; vertical-align: 9px" >
    
</form>
<br><br>

</body>
</html>

<?php
if (isset($_POST['submit'])) 
{
    // replace ' ' with '\ ' in the strings so they are treated as single command line args
    $TeamID1 = escapeshellarg($_POST[TeamID1]);
    $TeamID2 = escapeshellarg($_POST[TeamID2]);
    $Score1 = escapeshellarg($_POST[Score1]);
    $Score2 = escapeshellarg($_POST[Score2]);
    $Date = escapeshellarg($_POST[Date]);

    $command = '/home/mathursb/public_html/addGame.exe ' . $TeamID1 . ' ' . $TeamID2. ' ' . $Score1. ' ' .$Score2. ' ' .$Date;

    echo '<p style = "background-color:powderblue";>' . 'command: ' . $command . '</p>';
    // remove dangerous characters from command to protect web server
    $command = escapeshellcmd($command);
 
    // run odbc_insert_item.exe
    system($command);           
}
?>


