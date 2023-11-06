import com.mongodb.*;
import com.mongodb.client.*;
import org.bson.Document;
import com.mongodb.MongoClient;
import com.mongodb.client.result.UpdateResult;
import com.mongodb.client.result.DeleteResult;
import java.util.Scanner;
public class assignment12{
	public static void main(String args[]) {
		MongoClient mongoClient=new MongoClient("127.0.0.1",27017);
		MongoCredential credential=MongoCredential.createCredential("root","assignment","root123".toCharArray());
		System.out.println("Connected to the database");
		MongoDatabase database=mongoClient.getDatabase("assignment");
		MongoCollection<Document>collection=database.getCollection("javadatabase");
		Scanner sc=new Scanner(System.in);
		int ch=0;
		while(ch!=5) {
			System.out.println("Menu");
			System.out.println("1.Create");
			System.out.println("2.Read");
			System.out.println("3.Update");
			System.out.println("4. Delete");
			System.out.println("5.Exit");
			System.out.println("Enter your choice:");
			ch=sc.nextInt();
			switch(ch) {
			case 1:
				createDocument(collection,sc);
				break;
			case 2:
				readDocument(collection);
				break;
			case 3:
				updateDocument(collection,sc);
				break;
			case 4:
				deleteDocument(collection,sc);
				break;
			case 5:
				System.out.println("Exiting");
				break;
				
			}
			
		}
	}
	public static void createDocument(MongoCollection<Document>collection,Scanner sc) {
		System.out.println("Enter the key");
		String key=sc.next();
		System.out.println("Enter the value");
		String value=sc.next();
		Document document=new Document(key,value);
		collection.insertOne(document);
		System.out.println("Insert successful");
	}
	public static void readDocument(MongoCollection<Document>collection) {
		for(Document doc:collection.find()) {
			System.out.println(doc.toJson());
		}
	}
	public static void updateDocument(MongoCollection<Document>collection,Scanner sc) {
		System.out.println("Enter the key value to be updated");
		String key=sc.next();
		System.out.println("Enter the prev value: ");
		String prev_val=sc.next();
		System.out.println("Enter the new value: ");
		String new_val=sc.next();
		Document filter=new Document(key,prev_val);
		Document update=new Document("$set",new Document(key,new_val));
		UpdateResult rs=collection.updateMany(filter, update);
		System.out.println(rs);
		if(rs.getMatchedCount()>0) {
			System.out.println("Update was successful");
		}
		else {
			System.out.println("Error");
		}
	
		
	}
	public static void deleteDocument(MongoCollection<Document>collection,Scanner sc) {
		System.out.println("Enter the key to be deleted: ");
		String key=sc.next();
		System.out.println("Enter the value to be deleted: ");
		String val=sc.next();
		Document doc=new Document(key,val);
		DeleteResult rs=collection.deleteOne(doc);
		if(rs.getDeletedCount()>0) {
			System.out.println("Delete was successful");
		}
		else {
			System.out.println("Error");
		}
		
		}
}