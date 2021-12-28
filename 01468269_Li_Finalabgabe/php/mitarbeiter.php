<?php
  $user = 'a01468269';
  $pass = '271197';
  $database = 'lab';
 
  // establish database connection
  $conn = oci_connect($user, $pass, $database);
  if (!$conn) exit;
?>
<html>
<head></head>
<body>
<div>
	<a href='index.html'>Home</a>
  <form id='searchform' action='mitarbeiter.php' method='get'>
    <a href='mitarbeiter.php'>Alle Mitarbeitern</a>
     Suche nach Mitarbeiter_NachName:
    <input id='search' name='search' type='text' size='20' value='<?php echo $_GET['search']; ?>' />
    <input id='submit' type='submit' value='Los!' />
  </form>
</div>
<?php
  // check if search view of list view
  if (isset($_GET['search'])) {
    $sql = "SELECT * FROM mitarbeiter WHERE nachname like '%" . $_GET['search'] . "%'";
  } else {
    $sql = "SELECT * FROM mitarbeiter";
  }
 
  // execute sql statement
  $stmt = oci_parse($conn, $sql);
  oci_execute($stmt);
?>

<table style='border: 1px solid #DDDDDD'>
  <thead>
    <tr>
      <th>Vorname</th>
      <th>Nachname</th>
      <th>Gehalt</th>
      <th>Geschlecht</th>	    		
    </tr>
  </thead>
  <tbody>
<?php
  // fetch rows of the executed sql query
  while ($row = oci_fetch_assoc($stmt)) {
    echo "<tr>";
    echo "<td>" . $row['VORNAME'] . "</td>";
    echo "<td>" . $row['NACHNAME'] . "</td>";
    echo "<td>" . $row['GEHALT'] . "</td>";
    echo "<td>" . $row['GESCHLECHT'] . "</td>";
    echo "</tr>";
  }
?>
  </tbody>
 </table>
<div>Insgesamt <?php echo oci_num_rows($stmt); ?> Mitarbeitern gefunden!</div>
<?php  oci_free_statement($stmt); ?>

<div>
 <form id='insertform' action='mitarbeiter.php' method='get'>
   Neuen Mitarbeiter einfuegen:
      <table style='border: 1px solid #DDDDDD'>
         <thead>
            <tr>
               <th>vorname</th>
               <th>nachname</th>
               <th>gehalt</th>
		<th>geschlecht</th>
           </tr>
        </thead>
        <tbody>
           <tr>
               <td>
                  <input id='vorname' name='vorname' type='text' size='20' value='<?php echo $_GET['vorname']; ?>' />
               </td>
               <td>
                 <input id='nachname' name='nachname' type='text' size='20' value='<?php echo $_GET['nachname']; ?>' />
               </td>
               <td>
                 <input id='gehalt' name='gehalt' type='number' size='10' value='<?php echo $_GET['gehalt']; ?>' />
               </td>
		 <td>
		<input id='geschlecht' name='geschlecht' type='text' size='1' value='<?php echo $_GET['geschlecht']; ?>' />
		 </td>
             </tr>
          </tbody>
       </table>
       <input id='submit' type='submit' value='Insert!' />

 </form>
 </div>

<?php
 //Handle insert
 if (isset($_GET['vorname']))
 {
   //Prepare insert statementd
   $sql = "INSERT INTO mitarbeiter(vorname,nachname,gehalt,geschlecht,g_id) VALUES('" . $_GET['vorname'] . "','". $_GET['nachname'] ."'," . $_GET['gehalt'] .",'" . $_GET['geschlecht'] ."',1)";
   //Parse and execute statement
   $insert = oci_parse($conn, $sql);
   oci_execute($insert);
   $conn_err=oci_error($conn);
   $insert_err=oci_error($insert);
   if(!$conn_err & !$insert_err){
       print("Successfully inserted");
  print("<br>");
   }
   //Print potential errors and warnings
   else{
      print($conn_err);
      print_r($insert_err);
      print("<br>");
   }
   oci_free_statement($insert);
 }
 oci_close($conn);
?>
</body>
</html>