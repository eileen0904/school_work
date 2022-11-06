import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import org.w3c.dom.Attr;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import java.io.File;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

public class Create_XMLFile {
  static final String DB_URL = "jdbc:mysql://localhost/XMLDB";
  static final String USER = "root";
  static final String PASS = "123456";
  static final String QUERY = "SELECT id, first, last, nick, mark FROM class";

  public static void main(String argv[]) {
    try{
      DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
      DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
      Document doc = dBuilder.newDocument();

      Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
      Statement stmt = conn.createStatement();
      ResultSet rs = stmt.executeQuery(QUERY);

      // root element
      Element rootElement = doc.createElement("class");
      doc.appendChild(rootElement);
      while(rs.next()){
        // student element
        Element student = doc.createElement("student");
        rootElement.appendChild(student);
        // setting attribute to element
        Attr attr = doc.createAttribute("rollno");
        attr.setValue(Integer.toString(rs.getInt("id")));
        student.setAttributeNode(attr);
        // firstname element
        Element firstname = doc.createElement("firstname");
        firstname.appendChild(doc.createTextNode(rs.getString("first")));
        student.appendChild(firstname);
        // lastname element
        Element lastname = doc.createElement("lastname");
        lastname.appendChild(doc.createTextNode(rs.getString("last")));
        student.appendChild(lastname);
        // nickname element
        Element nickname = doc.createElement("nickname");
        nickname.appendChild(doc.createTextNode(rs.getString("nick")));
        student.appendChild(nickname);
         // marks element
        Element marks = doc.createElement("marks");
        marks.appendChild(doc.createTextNode(Integer.toString(rs.getInt("mark"))));
        student.appendChild(marks);
      }
      // write the content into xml file
      TransformerFactory transformerFactory = TransformerFactory.newInstance();
      Transformer transformer = transformerFactory.newTransformer();
      DOMSource source = new DOMSource(doc);
      StreamResult result = new StreamResult(new File("outputt.xml"));
      transformer.transform(source, result);
      // Output to console for testing
      StreamResult consoleResult = new StreamResult(System.out);
      transformer.transform(source, consoleResult);
    } catch (Exception e) {
      e.printStackTrace();
    }
  }
}
