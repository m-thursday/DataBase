<!-- <html>
<body>
<h3>Enter your name:</h3>

<form action="hello.php" method="post">
    Name: <input type="text" name="name"><br>
    <input name="submit" type="submit" >
</form>
<br><br>

</body>
</html> -->

<html>
<body style = "background-image: url('homescreen.png')"> 

<h1 style = "font-family: Impact; font-size:70px; background-color:#0000ff; text-align:center; color:#ffffff;" ><span>Hello! Welcome to the Database:</span></h1>

<div>
    <b><h2 style = "font-size:50px; text-align:center; color:#000000;">Menu:</h2></b>
    <table style = "font-size: 35px; margin: 0px auto; background-color:#000000; color:#ffffff;">
    <thead>
    <tr>
        <th>Option</th>
        <th>Function</th>
    </tr>
    </thead>
    <tbody>
    <tr>
    
        <td>1</td>
        <td><a href = "addGame.php"> Add New Game </a></td>
    </tr>
    <tr>
        <td>2</td>
        <td><a href = "addPlayer.php"> Add New Player </a></td>
    </tr>
    <tr>
        <td>3</td>
        <td><a href = "findPlayer.php"> Find Players (Team) </a></td>
    </tr>
    <tr>
        <td>4</td>
        <td><a href = "findPosition.php"> Find Players (Position) </a></td>
    </tr>
    <tr>
        <td>5</td>
        <td><a href = "viewRanking.php"> View Teams (Conference) </a></td>
    </tr>
    <tr>
        <td>6</td>
        <td><a href = "viewGame.php"> View Game (Team)</a></td>
    </tr>
    <tr>
        <td>7</td>
        <td><a href = "viewDate.php"> View Game (Date)</a></td>
    </tr>
    </tbody>
    </table>
</div>

<?php
if (isset($_POST['submit'])) 
{
    // replace ' ' with '\ ' in the strings so they are treated as single command line args
    $name = escapeshellarg($_POST[name]);

    // build the linux command that you want executed; use full path for safety
    $command = '/home/kevinz/public_html/project_cpp/hello.exe ' . $name;

    // remove dangerous characters from command to protect web server
    $command = escapeshellcmd($command);
 
    // echo then run the command
	echo "command: $command <br>";
    system($command);           
}
?>


