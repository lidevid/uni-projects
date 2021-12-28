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
  <form id='searchform' action='a.php' method='get'>
    <a href='a.php'>Alle Personen</a>
     Suche nach Name:
    <input id='search' name='search' type='text' size='20' value='<?php echo $_GET['search']; ?>' />
    <input id='submit' type='submit' value='Los!' />
  </form>
</div>
<?php
  // check if search view of list view
  if (isset($_GET['search'])) {
    $sql = "SELECT * FROM kunde WHERE nachname like '%" . $_GET['search'] . "%'";
  } else {
    $sql = "SELECT * FROM kunde";
  }
 
  // execute sql statement
  $stmt = oci_parse($conn, $sql);
  oci_execute($stmt);
?>

<table style='border: 1px solid #DDDDDD'>
  <thead>
    <tr>
      <th>kunde_id</th>
      <th>Vorname</th>
      <th>Nachname</th>
      <th>Email</th>
      <th>Betreuer_nr</th>	    		
    </tr>
  </thead>
  <tbody>
<?php
  // fetch rows of the executed sql query
  while ($row = oci_fetch_assoc($stmt)) {
    echo "<tr>";
    echo "<td>" . $row['KUNDE_ID'] . "</td>";
    echo "<td>" . $row['VORNAME'] . "</td>";
    echo "<td>" . $row['NACHNAME'] . "</td>";
    echo "<td>" . $row['EMAIL'] . "</td>";
    echo "<td>" . $row['BETREUER_PNR'] . "</td>";
    echo "</tr>";
  }
?>
  </tbody>
 </table>
<div>Insgesamt <?php echo oci_num_rows($stmt); ?> Person(en) gefunden!</div>
<?php  oci_free_statement($stmt); ?>

<div>
 <form id='insertform' action='a.php' method='get'>
   Neue Person einfuegen:
      <table style='border: 1px solid #DDDDDD'>
         <thead>
            <tr>
               <th>vorname</th>
               <th>nachname</th>
               <th>email</th>
               <th>betreuer_id</th>
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
                 <input id='email' name='email' type='text' size='20' value='<?php echo $_GET['email']; ?>' />
               </td>
               <td>
                 <input id='betreuer_pnr' name='betreuer_pnr' type='number' size='10' value='<?php echo $_GET['betreuer_pnr']; ?>' />
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
   $sql = "INSERT INTO kunde(vorname,nachname,email,betreuer_pnr) VALUES('"  . $_GET['vorname'] . "','" . $_GET['nachname'] . "','" . $_GET['email'] . "'," . $_GET  
   ['betreuer_pnr'] .")";
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
?>
<div>
 <form id='searchblum' action='a.php' method='get'>
   Suche name des Blumenstrauss(name):
     <input id='nachname' name='nachname' type='text' size='20' value='<?php echo $_GET['nachname']; ?>' />
     <input id='submit' type='submit' value='Aufruf Stored Procedure!' />
 </form>
</div>

<?php
 //Handle Stored Procedure
 if (isset($_GET['nachname']))
 {
    //Call Stored Procedure  
    $nachname = $_GET['nachname'];
    $name=[''];
    $sproc = oci_parse($conn, 'begin name_blume(:p1, :p2); end;');
    //Bind variables, p1=input (nachname), p2=output (blume)
    oci_bind_by_name($sproc, ':p1', $nachname);
    oci_bind_by_name($sproc, ':p2', $name);
    oci_execute($sproc);
    $conn_err=oci_error($conn);
    $proc_err=oci_error($sproc);
    //If there have been no Connection or Database errors, print department
    if(!$conn_err && !$proc_err){
       echo("<br><b>" . $nachname . " hat diesen Blumenstrauss gekauft - " . $name . "</b><br>" );  // prints OUT parameter of stored procedure
    }
    else{
      //Print potential errors and warnings
      print($conn_err);
      print_r($proc_err);
    }  
 }
 // clean up connections
 oci_free_statement($sproc);
 oci_close($conn);
?>

</body>
</html>