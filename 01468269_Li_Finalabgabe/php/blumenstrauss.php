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
  <form id='searchform' action='blumenstrauss.php' method='get'>
    <a href='blumenstrauss.php'>Alle Straeusse</a>
     Suche nach Artikel_Name:
    <input id='search' name='search' type='text' size='20' value='<?php echo $_GET['search']; ?>' />
    <input id='submit' type='submit' value='Los!' />
  </form>
</div>
<?php
  // check if search view of list view
  if (isset($_GET['search'])) {
    $sql = "SELECT * FROM blumenstrauss WHERE name like '%" . $_GET['search'] . "%'";
  } else {
    $sql = "SELECT * FROM blumenstrauss";
  }
 
  // execute sql statement
  $stmt = oci_parse($conn, $sql);
  oci_execute($stmt);
?>

<table style='border: 1px solid #DDDDDD'>
  <thead>
    <tr>
      <th>Artikel_nr</th>
      <th>Name</th>
      <th>Preise</th>
      <th>Kaufer_id</th>	    		
    </tr>
  </thead>
  <tbody>
<?php
  // fetch rows of the executed sql query
  while ($row = oci_fetch_assoc($stmt)) {
    echo "<tr>";
    echo "<td>" . $row['ARTIKEL_NR'] . "</td>";
    echo "<td>" . $row['NAME'] . "</td>";
    echo "<td>" . $row['PREISE'] . "</td>";
    echo "<td>" . $row['KAUFER_ID'] . "</td>";
    echo "</tr>";
  }
?>
  </tbody>
 </table>
<div>Insgesamt <?php echo oci_num_rows($stmt); ?> Blumenstraeusse gefunden!</div>
<?php  oci_free_statement($stmt); ?>

<div>
 <form id='insertform' action='blumenstrauss.php' method='get'>
   Neuen Strauss einfuegen:
      <table style='border: 1px solid #DDDDDD'>
         <thead>
            <tr>
               <th>name</th>
               <th>preise</th>
               <th>kaufer_id</th>
           </tr>
        </thead>
        <tbody>
           <tr>
               <td>
                  <input id='name' name='name' type='text' size='20' value='<?php echo $_GET['name']; ?>' />
               </td>
               <td>
                 <input id='preise' name='preise' type='number' size='5' value='<?php echo $_GET['preise']; ?>' />
               </td>
               <td>
                 <input id='kaufer_id' name='kaufer_id' type='number' size='10' value='<?php echo $_GET['kaufer_id']; ?>' />
               </td>
             </tr>
          </tbody>
       </table>
       <input id='submit' type='submit' value='Insert!' />

 </form>
 </div>

<?php
 //Handle insert
 if (isset($_GET['name']))
 {
   //Prepare insert statementd
   $sql = "INSERT INTO blumenstrauss(name,preise,kaufer_id) VALUES('" . $_GET['name'] . "'," . $_GET['preise'] ."," . $_GET[kaufer_id] .")";
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