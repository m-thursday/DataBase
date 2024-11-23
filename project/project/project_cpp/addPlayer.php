
<html style = "background-image: url('addPlayer.png'); background-repeat: no-repeat; background-size: 100% 100%; background-attachment: fixed;">
<body>
<body>
<h3 style = "font-family: Impact; font-size:60px; background-color:#0000ff; text-align:center; color:#ffffff;">Enter information about a player to add to the database:</h3>

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

<form align = "center" style = "background-color:#00ffff" action="addPlayer.php" method="post">
<b><a href = "hello.php"><br> <input type = "button" value = "Back" style = "background-color:white; border: solid 3px #6e6e6e; height: 30px; vertical-align: 9px"/></a></b><br>

    Team ID: <input type="text" name="TeamID"><br>
    Name: <input type="text" name="Name"><br>
    Position: <select name="Position" id = "Position"><br>
            <option value = "Select">Select</option>
            <option value = "Offensive Line">Offensive Line</option>
            <option value = "Quarterback">Quarterback</option>
            <option value = "Running Back">Running Back</option>
            <option value = "Wide Receiver">Wide Receiver</option>
            <option value = "Tight End">Tight End</option>
            <option value = "Defensive Line">Defensive Line</option>
            <option value = "Linebacker">Linebacker</option>
            <option value = "Cornerback">Cornerback</option>
            <option value = "Safety">Safety</option>
            <option value = "Special Teams">Special Teams</option><br>
    <br><input name="submit" type="submit" style = "background-color:green; border: solid 3px #6e6e6e; height: 30px; vertical-align: 9px" >
</form>
<br><br>

</body>
</html>

<?php
if (isset($_POST['submit'])) 
{
    // replace ' ' with '\ ' in the strings so they are treated as single command line args
    $TeamID = escapeshellarg($_POST[TeamID]);
    $Name = escapeshellarg($_POST[Name]);
    $Position = escapeshellarg($_POST[Position]);


    $command = '/home/mathursb/public_html/addPlayer.exe ' . $TeamID . ' ' . $Name. ' ' . $Position;

    echo '<p>' . 'command: ' . $command . '<p>';
    // remove dangerous characters from command to protect web server
    $command = escapeshellcmd($command);
 
    // run odbc_insert_item.exe
    system($command);           
}
?>


