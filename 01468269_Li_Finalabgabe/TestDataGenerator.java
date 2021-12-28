import java.sql.*;
import oracle.jdbc.driver.*;
import java.util.Random;

public class TestDataGenerator {

  public static void main(String args[]) {

    try {
      Class.forName("oracle.jdbc.driver.OracleDriver");
      String database = "jdbc:oracle:thin:@131.130.122.4:1521:lab";
      String user = "a01468269";
      String pass = "271197";

      // establish connection to database 
      Connection con = DriverManager.getConnection(database, user, pass);
      Statement stmt = con.createStatement();

      // Blumen Geschaeft
      try {
        String insertSql = "INSERT INTO blumen_geschaeft VALUES (1,'The Flos','Wien',1050,'Mariahilferstrasse,12')";
        stmt.executeUpdate(insertSql);
      } catch (Exception e) {
        System.err.println("Fehler beim Einfuegen des Datensatzes in geschaeft: " + e.getMessage());
      }
      
      //Blumen
      {
    	  
    	  for(int i=1;i<=4000;i++)
    	  {
    		  String insertSql = "INSERT INTO blume(sorte,g_id,anzahl,preise) VALUES ('Rosa_"+i+"',1,"+(int)((Math.random()*1000)+1)+","+(int)((Math.random()*10)+1)+")";
    	  try{
    	  stmt.executeUpdate(insertSql);
    	  }catch (Exception e){
    	  System.err.println("Fehler beim Einfuegen des Datensatzes in blume: " + e.getMessage());
      }
    	  }
      }
      
      //Lager
      {
    	  for(int i=1;i<=5;i++)
    	  {
    		  String insertSql="INSERT INTO lager(g_id,grundflaeche,temperatur) VALUES (1,"+(int)((Math.random()*20)+1)+","+(int)((Math.random()*10)+20)+")";
    	  try{
    		  stmt.executeUpdate(insertSql);
    	  }catch(Exception e){
    		  System.err.println("Fehler beim Einfuegen des Datensatzes in lager: " + e.getMessage());
    	  }
    	  }
      }

    //Einlagern
      {
    	  String[] monat= {"Jan", "Feb", "Mar", "Apr", "May", "June", "July", "Aug", "Sep", "Oct", "Nov", "Dec"};
    	  int tag=0;
    	  for(int i=1;i<=2000;i++)
    	  {
    		  String neue_monat= (monat[(int)(Math.random() * 11)]);
    		  if(neue_monat=="Jan"  || neue_monat=="Mar" || neue_monat=="May" || neue_monat=="July" || neue_monat=="Aug" || neue_monat=="Oct" || neue_monat=="Dec")
    		  {
    			  tag=((int)((Math.random() * 30)+1));
    		  }
    		  else if(neue_monat=="Apr"  || neue_monat=="June" || neue_monat=="Sep" || neue_monat=="Nov")
    		  {
    			  tag=((int)((Math.random() * 29)+1));
    		  }
    		  else if(neue_monat=="Feb")
    		  {
    			  tag=((int)((Math.random() * 27)+1));
    		  }
    		  
    		  String insertSql="INSERT INTO einlagern(lager_id,g_id,blume_id,lieferungsdatum) VALUES ("+(int)((Math.random()*4)+1)+",1,"+i+",'"+tag+"-"+neue_monat+"-"+(int)((Math.random()*2)+2017)+"')";
    	  try{
    		  stmt.executeUpdate(insertSql);
    	  }catch(Exception e){
    		  System.err.println("Fehler beim Einfuegen des Datensatzes in einlagern: " + e.getMessage());
    	  }
    	  }
      }
      
    //Mitarbeiter
      {
    	  String[] geschlecht={"w","m"};
    	  for(int i=1;i<=15;i++)
    	  {
    		String sex=(geschlecht[(int)((Math.random())+0.5)]);
    		  String insertSql="INSERT INTO mitarbeiter(vorname,nachname,gehalt,geschlecht,g_id) VALUES ('John"+i+"','Smith"+i+"',"+(int)((Math.random()*5000)+500)+",'"+sex+"',1)";
    	  try{
    		  stmt.executeUpdate(insertSql);
    	  }catch(Exception e){
    		  System.err.println("Fehler beim Einfuegen des Datensatzes in mitarbeiter: " + e.getMessage());
    	  }
    	  }
      }
      
      //is_boss
      {
    	  try{
    		  String insertSql="INSERT INTO is_boss VALUES (1,2)";
    		  stmt.executeUpdate(insertSql);
    	  }catch(Exception e){
    		  System.err.println("Fehler beim Einfuegen des Datensatzes in is_boss: " + e.getMessage());
    	  }
      }
      
    //freelancer
      {
    	  try{
    		  String insertSql="INSERT INTO freelancer VALUES ('designer123@gmail.com',20,NULL,1)";
    		  stmt.executeUpdate(insertSql);
    	  }catch(Exception e){
    		  System.err.println("Fehler beim Einfuegen des Datensatzes in freelancer: " + e.getMessage());
    	  }
      }
      
    //Festangestellter
      {
    	  for(int i=3;i<=15;i++)
    	  {
    		  String insertSql="INSERT INTO festangestellter VALUES ("+(int)((Math.random()*10000)+10000)+","+(int)(Math.random()*100)+","+i+")";
    	  try{
    		  stmt.executeUpdate(insertSql);
    	  }catch(Exception e){
    		  System.err.println("Fehler beim Einfuegen des Datensatzes in festangestellter: " + e.getMessage());
    	  }
    	  }
      }
      
    //Kunde
      {
    	  for(int i=1;i<=1000;i++)
    	  {
    		  String insertSql="INSERT INTO kunde(vorname,nachname,betreuer_pnr,email) VALUES ('Patrick"+i+"','Star"+i+"',"+(int)((Math.random()*14)+1)+",'fake_email"+i+"@gmail.com')";
    	  try{
    		  stmt.executeUpdate(insertSql);
    	  }catch(Exception e){
    		  System.err.println("Fehler beim Einfuegen des Datensatzes in kunde: " + e.getMessage());
    	  }
    	  }
      }
      
    //Lieferant
      {
    	  for(int i=1;i<=5;i++)
    	  {
    		  String insertSql="INSERT INTO lieferant(adresse,name) VALUES('Waaggasse"+(int)((Math.random()*100)+1)+"','ProGarden"+i+"')";
    	  try{
    		  stmt.executeUpdate(insertSql);
    	  }catch(Exception e){
    		  System.err.println("Fehler beim Einfuegen des Datensatzes in lieferant: " + e.getMessage());
    	  }
    	  }
      }
      
      //Blumenstrauss
      {
    	  for(int i=1;i<=100;i++)
    	  {
    		  String insertSql="INSERT INTO blumenstrauss(name,preise,kaufer_id) VALUES('Spring Breath"+i+"',"+(int)(Math.random()*200)+","+(int)((Math.random()*999)+1)+")";
    	  try{
    		  stmt.executeUpdate(insertSql);
    	  }catch(Exception e){
    		  System.err.println("Fehler beim Einfuegen des Datensatzes in blumenstrauss: " + e.getMessage());
    	  }
    	  }
      }
      
    //Blumen-lieferant-strauss
      {
    	  for(int i=1;i<=1000;i++)
    	  {
    		  String insertSql="INSERT INTO blumen_lieferant_strauss VALUES("+(int)((Math.random()*3999)+1)+","+(int)((Math.random()*4)+1)+","+(int)((Math.random()*99)+1)+")";
;    	  try{
    		  stmt.executeUpdate(insertSql);
    	  }catch(Exception e){
    		  System.err.println("Fehler beim Einfuegen des Datensatzes in b_l_s: " + e.getMessage());
    	  }
    	  }
      }
      
      
      
      // check number of datasets in person table
      ResultSet rs = stmt.executeQuery("SELECT COUNT(*) FROM blumen_geschaeft");
      if (rs.next()) {
        int count = rs.getInt(1);
        System.out.println("Number of datasets in the table blumen_geschaeft: " + count);
      }
      ResultSet rs1 = stmt.executeQuery("SELECT COUNT(*) FROM blume");
      if (rs1.next()) {
        int count = rs1.getInt(1);
        System.out.println("Number of datasets in the table blume: " + count);
      }
      ResultSet rs2 = stmt.executeQuery("SELECT COUNT(*) FROM lager");
      if (rs2.next()) {
        int count = rs2.getInt(1);
        System.out.println("Number of datasets in the table lager: " + count);
      }
      ResultSet rs3 = stmt.executeQuery("SELECT COUNT(*) FROM einlagern");
      if (rs3.next()) {
        int count = rs3.getInt(1);
        System.out.println("Number of datasets in the table einlagern: " + count);
      }
      ResultSet rs4 = stmt.executeQuery("SELECT COUNT(*) FROM mitarbeiter");
      if (rs4.next()) {
        int count = rs4.getInt(1);
        System.out.println("Number of datasets in the table mitarbeiter: " + count);
      }
      ResultSet rs5 = stmt.executeQuery("SELECT COUNT(*) FROM is_boss");
      if (rs5.next()) {
        int count = rs5.getInt(1);
        System.out.println("Number of datasets in the table is_boss: " + count);
      }
      ResultSet rs6 = stmt.executeQuery("SELECT COUNT(*) FROM freelancer");
      if (rs6.next()) {
        int count = rs6.getInt(1);
        System.out.println("Number of datasets in the table freelancer: " + count);
      }
      ResultSet rs7 = stmt.executeQuery("SELECT COUNT(*) FROM festangestellter");
      if (rs7.next()) {
        int count = rs7.getInt(1);
        System.out.println("Number of datasets in the table festangestellter: " + count);
      }
      ResultSet rs8 = stmt.executeQuery("SELECT COUNT(*) FROM kunde");
      if (rs8.next()) {
        int count = rs8.getInt(1);
        System.out.println("Number of datasets in the table kunde: " + count);
      }
      ResultSet rs9 = stmt.executeQuery("SELECT COUNT(*) FROM lieferant");
      if (rs9.next()) {
        int count = rs9.getInt(1);
        System.out.println("Number of datasets in the table lieferant: " + count);
      }
      ResultSet rs0 = stmt.executeQuery("SELECT COUNT(*) FROM blumenstrauss");
      if (rs0.next()) {
        int count = rs0.getInt(1);
        System.out.println("Number of datasets in the table blumenstrauss: " + count);
      }
      ResultSet rs11 = stmt.executeQuery("SELECT COUNT(*) FROM blumen_lieferant_strauss");
      if (rs11.next()) {
        int count = rs11.getInt(1);
        System.out.println("Number of datasets in the table b_l_s: " + count);
      }

      // clean up connections
      rs.close();
      stmt.close();
      con.close();

    } catch (Exception e) {
      System.err.println(e.getMessage());
    }
  }
}