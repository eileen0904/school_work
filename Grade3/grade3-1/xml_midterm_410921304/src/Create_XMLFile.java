import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import org.w3c.dom.Attr;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.io.PrintWriter;
import java.io.FileOutputStream;
import javax.xml.transform.OutputKeys;

public class Create_XMLFile {
  static final String DB_URL = "jdbc:mysql://localhost/XMLMID";
  static final String USER = "root";
  static final String PASS = "123456";
  static final String QUERY = "SELECT student_id, xml_class, data_structure, algorithm, network FROM score_data";

  public static String getGPA(Integer score){
    if(score <= 100 && score >= 90) return "4.5";
    if(score <= 89 && score >= 85) return "4.0";
    if(score <= 84 && score >= 80) return "3.7";
    if(score <= 79 && score >= 77) return "3.3";
    if(score <= 76 && score >= 73) return "3.0";
    if(score <= 72 && score >= 70) return "2.7";
    if(score <= 69 && score >= 67) return "2.5";
    if(score <= 66 && score >= 63) return "2.3";
    if(score <= 62 && score >= 60) return "2.0";
    if(score <= 59 && score >= 50) return "1.0";
    return "0.0";
  }
  public static void main(String argv[]) {
    try{
      DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
      DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
      Document doc = dBuilder.newDocument();

      Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
      Statement stmt = conn.createStatement();
      ResultSet rs = stmt.executeQuery(QUERY);

      // root element
      Element rootElement = doc.createElement("score_data");
      doc.appendChild(rootElement);
      while(rs.next()){
        // student element
        Element student = doc.createElement("student");
        rootElement.appendChild(student);
        // setting attribute to element
        Attr id_attr = doc.createAttribute("student_id");
        id_attr.setValue(rs.getString("student_id"));
        student.setAttributeNode(id_attr);

        // xml_class element
        Element xml_class = doc.createElement("xml_class");
        xml_class.appendChild(doc.createTextNode(Integer.toString(rs.getInt("xml_class"))));
        student.appendChild(xml_class);
        // setting attribute to element
        Attr xml_attr = doc.createAttribute("gpa");
        String xml_gpa = getGPA(rs.getInt("xml_class"));
        xml_attr.setValue(xml_gpa);
        xml_class.setAttributeNode(xml_attr);

        // data_structure element
        Element data_structure = doc.createElement("data_structure");
        data_structure.appendChild(doc.createTextNode(Integer.toString(rs.getInt("data_structure"))));
        student.appendChild(data_structure);
        // setting attribute to element
        Attr ds_attr = doc.createAttribute("gpa");
        String ds_gpa = getGPA(rs.getInt("data_structure"));
        ds_attr.setValue(ds_gpa);
        data_structure.setAttributeNode(ds_attr);

        // algorithm element
        Element algorithm = doc.createElement("algorithm");
        algorithm.appendChild(doc.createTextNode(Integer.toString(rs.getInt("algorithm"))));
        student.appendChild(algorithm);
        // setting attribute to element
        Attr algo_attr = doc.createAttribute("gpa");
        String algo_gpa = getGPA(rs.getInt("algorithm"));
        algo_attr.setValue(algo_gpa);
        algorithm.setAttributeNode(algo_attr);

        // network element
        Element network = doc.createElement("network");
        network.appendChild(doc.createTextNode(Integer.toString(rs.getInt("network"))));
        student.appendChild(network);
        // setting attribute to element
        Attr net_attr = doc.createAttribute("gpa");
        String net_gpa = getGPA(rs.getInt("network"));
        net_attr.setValue(net_gpa);
        network.setAttributeNode(net_attr);
      }
      // write the content into xml file
      TransformerFactory transformerFactory = TransformerFactory.newInstance();
      Transformer transformer = transformerFactory.newTransformer();
      DOMSource source = new DOMSource(doc);
      transformer.setOutputProperty(OutputKeys.INDENT, "yes"); //縮進
      PrintWriter pw = new PrintWriter(new FileOutputStream("output.xml"));
      StreamResult result = new StreamResult(pw);
      transformer.transform(source, result);
      // Output to console for testing
      StreamResult consoleResult = new StreamResult(System.out);
      transformer.transform(source, consoleResult);
    } catch (Exception e) {
      e.printStackTrace();
    }
  }
}
