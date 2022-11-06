import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;

public class CreateTable {
  static final String DB_URL = "jdbc:mysql://localhost:3306/XMLMID";
  static final String USER = "root";
  static final String PASS = "123456";

  public static void main(String[] args) {
    // Open a connection
    try{
      Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
      Statement stmt = conn.createStatement();      
      String sql = "CREATE TABLE score_data" +
                "(student_id VARCHAR(5) not NULL, " +
                " xml_class INTEGER, " + 
                " data_structure INTEGER, " + 
                " algorithm INTEGER, " + 
                " network INTEGER, " + 
                " PRIMARY KEY ( student_id ))"; 
      stmt.executeUpdate(sql);
      System.out.println("Created table in given database...");   	  
    } 
    catch(SQLException e){
      e.printStackTrace();
    } 
  }
}
