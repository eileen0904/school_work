import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;

public class DeleteTable {
    static final String DB_URL = "jdbc:mysql://localhost:3306/XMLMID";
    static final String USER = "root";
    static final String PASS = "123456";

    public static void main(String[] args){
        try{
            Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
            Statement stmt = conn.createStatement();
            String sql = "DROP TABLE score ";
            stmt.executeUpdate(sql);
            System.out.println("Table  deleted in given database...");
        }
        catch(SQLException e){
            e.printStackTrace();
        } 
    }
}
