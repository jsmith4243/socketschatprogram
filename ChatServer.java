import java.lang.*;
import java.net.*;
import java.io.*;
import java.util.*;


public class ChatServer extends Thread {


	private ServerSocket serverSocket;
	
	public ChatServer(int port) throws IOException 
	{
	
		serverSocket = new ServerSocket(port);
		
		serverSocket.setSoTimeout(20000);
	
	
	}
	
	public void run()
	{
	
	
		while(true)
		{
		
	
			try 
			{
			
				System.out.println("Listening for connection on port: " + serverSocket.getLocalPort() + ".");
				
				Socket server = serverSocket.accept();
				
				System.out.println("A client has connected with the address: " + server.getRemoteSocketAddress());
				System.out.println("\n");
				
				//DataInputStream in = new DataInputStream(server.getInputStream());
				BufferedReader in = new  BufferedReader( new InputStreamReader(server.getInputStream()));
				
				
				
				//DataOutputStream out = new DataOutputStream(server.getOutputStream());
				PrintWriter out = new PrintWriter(server.getOutputStream(), true);
				
				String clientUsername;
				
				String response;
				String request;

				String serverUsername;
				
				//System.out.println(in.readUTF());
				//System.out.println(in.readLine());
				
				

				
				//out.println("Thank you for connecting to " + server.getLocalSocketAddress() + "\nGoodbye!");
				
				Scanner keyboard = new Scanner(System.in);
				
				
				System.out.print("Please enter your username: ");
				serverUsername = keyboard.nextLine();
				System.out.print("\n");
				out.println(serverUsername);
				
				

				clientUsername = in.readLine();
				//System.out.println("client username is: " + clientUsername);
				
				
				
				while(true)
				{
				
					//BufferedReader in = new  BufferedReader( new InputStreamReader(server.getInputStream()));
					
					//System.out.println("looping");
				
					
					request = in.readLine();
					System.out.println(clientUsername + ": " + request);
					
				
					
					
					
					//System.out.println(clientUsername + ": " + in.readLine());
					
					
					
					System.out.print("Please enter your message: ");
					response = keyboard.nextLine();
					if (response.equals( "\\quit"))
					{
						//System.out.println("QUIT TRIGGERED");
						server.close();
						System.exit(1);
						
					}
					System.out.println(serverUsername + ": " + response);
					out.println(response);
					
					
					
				
				}
				
				//server.close();
				
			}
			
			catch(SocketTimeoutException s) 
			{
			
				System.out.println("Socket timed out!");
				
				break;
				
			} 
			
			catch(IOException e) 
			{
			
				e.printStackTrace();
				
				break;
				
			}
			
			//server.close();
			
		}
		
	}
	
	public static void main(String[] args) 
	{
	
		int port = Integer.parseInt(args[0]);
		
		try {
		
			System.out.println("Welcome to the chat server.\n");
		
			Thread t = new ChatServer(port);
			
			t.start();
		
		}
		
		catch(IOException e) 
		{
		
			e.printStackTrace();
		
		}
	}

		
		




}