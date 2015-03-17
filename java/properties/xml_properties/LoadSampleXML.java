import java.util.*;  
import java.io.*;  

public class LoadSampleXML {
    public static void main(String args[]) throws Exception {
        Properties prop = new Properties();  
        FileInputStream fis =  
            new FileInputStream("sampleprops.xml");  
        prop.loadFromXML(fis);  
        prop.list(System.out);  
        System.out.println("\nThe foo property: " +  
                prop.getProperty("foo"));  
    }  
}  
