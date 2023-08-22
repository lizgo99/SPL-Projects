package bgu.spl.net.impl.stomp;

import java.io.IOException;
import java.util.HashMap;

import bgu.spl.net.srv.Connections;

public class ConnectionsImpl <T> implements Connections <T> {

    public HashMap<String, HashMap<Integer, String>> map = new HashMap<>(); // <Channel,<ConnectionID,SubscriptionID>>
    public HashMap<Integer,User> connectionIdToUsers= new HashMap<>(); //<ConnectionID,User>
    
    // we need to see if those functions need to be public/protected/private


    public boolean send(int connectionId, T msg){ 
        return true;
    }

    public void send(String channel, T msg){

    }

    public void disconnect(int connectionId){

    }

    public User getUser(Integer connectionID){
        return connectionIdToUsers.get(connectionID);
    }
}
