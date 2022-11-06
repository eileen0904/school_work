import java.io.File;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;

import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;
import org.w3c.dom.Document;
import org.w3c.dom.NodeList;
import org.w3c.dom.Node;
import org.w3c.dom.Element;

public class InsertToSQL{
  static final String DB_URL = "jdbc:mysql://localhost/XMLMID";
	static final String USER = "root";
	static final String PASS = "123456";

  public static void main(String[] args){
    try{
      File inputFile = new File("score_data.xml");
      DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
      DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
      Document doc = dBuilder.parse(inputFile);
      doc.getDocumentElement().normalize();

      System.out.println("Root element : " + doc.getDocumentElement().getNodeName());
      NodeList nList = doc.getElementsByTagName("student");
      System.out.println("----------------------------");

      for(int temp = 0; temp < nList.getLength(); temp++){
        Node nNode = nList.item(temp);
        System.out.println("\nCurrent Element : " + nNode.getNodeName());
        String sql = "INSERT INTO score_data VALUES (";

        if(nNode.getNodeType() == Node.ELEMENT_NODE){
          Element eElement = (Element) nNode;
          System.out.println("Student_id : " + eElement.getAttribute("student_id"));
          sql = sql + "'" + eElement.getAttribute("student_id") + "', ";
          System.out.println("Xml_class : " + eElement.getElementsByTagName("xml_class").item(0).getTextContent());
          sql = sql + eElement.getElementsByTagName("xml_class").item(0).getTextContent() + ", ";
          System.out.println("Data_structure : " + eElement.getElementsByTagName("data_structure").item(0).getTextContent());
          sql = sql + eElement.getElementsByTagName("data_structure").item(0).getTextContent() + ", ";
          System.out.println("Algorithm : " + eElement.getElementsByTagName("algorithm").item(0).getTextContent());
          sql = sql + eElement.getElementsByTagName("algorithm").item(0).getTextContent() + ", ";
          System.out.println("Network : " + eElement.getElementsByTagName("network").item(0).getTextContent());
          sql = sql + eElement.getElementsByTagName("network").item(0).getTextContent() + ")";

          try{
            Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
            Statement stmt = conn.createStatement();
            stmt.executeUpdate(sql);
          }catch(SQLException e){
            e.printStackTrace();
          } 
        }
      }
    }catch (Exception e){
      e.printStackTrace();
    }
  }
}
