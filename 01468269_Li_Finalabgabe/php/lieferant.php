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
  <form id='searchform' action='lieferant.php' method='get'>
    <a href='lieferant.php'>Alle Liefer_firmen</a>
     Suche nach Firma_name:
    <input id='search' name='search' type='text' size='20' value='<?php echo $_GET['search']; ?>' />
    <input id='submit' type='submit' value='Los!' />
  </form>
</div>
<?php
  // check if search view of list view
  if (isset($_GET['search'])) {
    $sql = "SELECT * FROM lieferant WHERE name like '%" . $_GET['search'] . "%'";
  } else {
    $sql = "SELECT * FROM lieferant";
  }
 
  // execute sql statement
  $stmt = oci_parse($conn, $sql);
  oci_execute($stmt);
?>

<table style='border: 1px solid #DDDDDD'>
  <thead>
    <tr>
      <th>Firma_id</th>
      <th>Adresse</th>
      <th>Name</th>
   </tr>
  </thead>
  <tbody>
<?php
  // fetch rows of the executed sql query
  while ($row = oci_fetch_assoc($stmt)) {
    echo "<tr>";
    echo "<td>" . $row['FIRMA_ID'] . "</td>";
    echo "<td>" . $row['ADRESSE'] . "</td>";
    echo "<td>" . $row['NAME'] . "</td>";
    echo "</tr>";
  }
?>
  </tbody>
 </table>
<div>Insgesamt <?php echo oci_num_rows($stmt); ?> Firmen gefunden!</div>
<?php  oci_free_statement($stmt); ?>

<div>
 <form id='insertform' action='lieferant.php' method='get'>
   Neuen Firma einfuegen:
      <table style='border: 1px solid #DDDDDD'>
         <thead>
            <tr>
               <th>Adresse</th>
               <th>Name</th>
           </tr>
        </thead>
        <tbody>
           <tr>
               <td>
                  <input id='adresse' name='adresse' type='text' size='30' value='<?php echo $_GET['adresse']; ?>' />
               </td>
               <td>
                 <input id='name' name='name' type='text' size='20' value='<?php echo $_GET['name']; ?>' />
               </td>
             </tr>
          </tbody>
       </table>
       <input id='submit' type='submit' value='Insert!' />

 </form>
 </div>

<?php
 //Handle insert
 if (isset($_GET['adresse']))
 {
   //Prepare insert statementd
   $sql = "INSERT INTO lieferant(adresse,name) VALUES('" . $_GET['adresse'] . "','". $_GET['name'] ."')";
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