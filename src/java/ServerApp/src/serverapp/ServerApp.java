/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package serverapp;

import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

/**
 *
 * @author smolina
 */
public class ServerApp {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        try(ServerSocket server = new ServerSocket(9000)){
            System.out.println("Server listenning for incomming connections...");
            while(true){
                try(Socket client = server.accept()){
                    System.out.println("Connection from "+ client.getInetAddress().toString());
                    InputStream is = client.getInputStream();
                    OutputStream os = client.getOutputStream();
                    final int bufferSize = 1024;
                    
                    byte [] data = new byte[bufferSize];
                    int bytesRead = is.read(data, 0, bufferSize);
                    os.write(data, 0, bytesRead);
                }
            }
        }catch(Throwable t){
            t.printStackTrace();
        }
    }
    
}
