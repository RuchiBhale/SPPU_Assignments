package demo;
import java.util.*;
import java.sql.*;
public class assignment8 {
	public static Connection con;
	public static void checkConnection() {
		try {
			Class.forName("com.mysql.cj.jdbc.Driver");
			con=DriverManager.getConnection("jdbc:mysql://127.0.0.1/db1","root","root123");
			if(con!=null && !con.isClosed()) {
				System.out.println("Successful");
			
			}
			else {
				System.out.println("Connection failed");
			}
		}catch(SQLException e) {
			System.out.println("Error occurred");
		}
		catch(Exception e) {
			System.out.println(e);
		}
	}
	public static void create_table(String table_name,String rollno,String name) {
		try {
			
		
		String sql="create table "+table_name+"("+rollno+" int primary key, "+name+" varchar(25));";
		PreparedStatement ps=con.prepareStatement(sql);
		ps.executeUpdate();
		System.out.println("Table created successfully!");
		}catch(SQLException e) {
			System.out.println(e);
		}
		
	}
	public static void insertion(String table_name,int rollno,String name) {
		try {
		String sql="insert into "+table_name+" values("+rollno+",'"+name+"');";
		System.out.println(sql);
		PreparedStatement ps=con.prepareStatement(sql);
		int affected=ps.executeUpdate();
		if(affected>0) {
			System.out.println("Inserted data");
		}
		else {
			System.out.println("Error occured");
		}
		}catch(SQLException e) {
			System.out.println(e);
		}
	}
	public static void update(String table_name,int rollno,String name) {
		try {
			String sql="update "+table_name+" set name='"+name+"' where rollno="+rollno+";";
			PreparedStatement ps=con.prepareStatement(sql);
			int affected=ps.executeUpdate();
			if(affected>0) {
				System.out.println("Update was successful");
			}
			else {
				System.out.println("Error");
			}
		}catch(SQLException e) {
			System.out.println(e);
		}
	}
	public static void deletion(String table_name,int rollno) {
		try {
			String sql="delete from "+table_name+" where rollno="+rollno+";";
			PreparedStatement ps=con.prepareStatement(sql);
			int affected=ps.executeUpdate();
			if(affected>0) {
				System.out.println("Deleted succesfully");
			}
			else {
				System.out.println("Error");
			}
		}catch(SQLException e) {
			System.out.println(e);
		}
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner sc=new Scanner(System.in);
		int ch=99;
		String table_name="";
		while(ch!=0) {
			
		
		System.out.println("1.Check Connection");
		System.out.println("2.Create table");
		System.out.println("3.Insert data");
		System.out.println("4.Update record");
		System.out.println("5.Delete record");
		System.out.println("6.Exit");
		
		ch=sc.nextInt();
		switch(ch) {
		case 1:
			checkConnection();
			break;
		case 2:
			System.out.println("Enter the name of the table: ");
			table_name=sc.next();
			create_table(table_name,"Rollno","Name");
			break;
		case 3:
			System.out.println("Enter the rollno and Name of the student: ");
			int rollno=sc.nextInt();
			String name=sc.next();
			insertion(table_name,rollno,name);
			break;
		case 4:
			System.out.println("Enter the rollno to be updated and the new name: ");
			int roll=sc.nextInt();
			String new_name=sc.next();
			update(table_name,roll,new_name);
			break;
		case 5:
			System.out.println("Enter the rollno to be deleted: ");
			int roll_no=sc.nextInt();
			deletion(table_name,roll_no);
			break;
		case 6:
			System.out.println("Exit");
			break;
		
		}
		}
		sc.close();
		
		

	}

}
