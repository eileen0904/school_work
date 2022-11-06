import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;

public class CreateSchema {
  //JDBC Driver
  static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";
  static final String DB_URL = "jdbc:mysql://localhost:3306";
  static final String USER = "root";
  static final String PASS = "123456";

  public static void main(String[] args){
    try{
      Class.forName(JDBC_DRIVER);
    }
    catch(ClassNotFoundException es){
      System.out.println("Not found MySQL JDBC Driver");
      es.printStackTrace();
      return;
    }

    try{
      Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
      Statement stmt = conn.createStatement();
      String sql = "CREATE DATABASE XMLDB";
      stmt.executeUpdate(sql);
      System.out.println("Database created successfully...");   	  
    }
    catch(SQLException e){
      System.out.println("Connection Failed! Check output console");
      e.printStackTrace();
    } 
  }
}
