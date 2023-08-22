package bgu.spl.net.impl.stomp;

import java.util.HashMap;

import javax.xml.transform.Templates;

import bgu.spl.net.srv.Connections;
public class StompMessagingProtocolImpl<T>  {

    private boolean shouldTerminate = false;
    private ConnectionsImpl<T> connections;
    private Integer connectionId;



	/**
	 * Used to initiate the current client protocol with it's personal connection ID and the connections implementation
	**/
    public void start(int connectionId, ConnectionsImpl<T> connections){
        //we need to check if we need any changes
        this.connectionId = connectionId;
        this.connections = connections;
        
    }
    
    public void process(T message){
        Frame<T> frame =  new Frame<T>(message);
        frameCommandType commandType = frame.getCommandType();
        if(commandType==frameCommandType.CONNECT){
            
        }
        if(commandType==frameCommandType.SEND){
            
        }

        if(commandType==frameCommandType.SUBSCRIBE){
            //check if the frame is valid
           if(true){
                String receipt = handleSubscribe(frame);
               // connections.send(connectionId, (T)receipt); // notice that we did cating to T because he didnt exept without it.
            }
           else{
                //Eror function
           }

        }

        if(commandType==frameCommandType.UNSUBSCRIBE){
            //check if the frame is valid
            if(true){
                String receipt = handleUnSubscribe(frame);
               // connections.send(connectionId, (T)receipt); // notice that we did cating to T because he didnt exept without it.
            }
           else{
                //Eror function
           }
        }
        if(commandType==frameCommandType.DISCONNECT){
            
        }

    }
	
	/**
     * @return true if the connection should be terminated
     */
    public boolean shouldTerminate(){
        return shouldTerminate ;
    }

    private String handleSubscribe(Frame<T> frame){
        String channel = (String)frame.headers.get("destination");
        String subscriprionID = (String)frame.headers.get("id");
        String receiptID = (String)frame.headers.get("receipt");
        String[] teamNames = channel.split("_");
        String reverseChannel = teamNames[1] + "_" + teamNames[0];
        User user = connections.getUser(connectionId);

        if(connections.map.containsKey(channel)){ // the channel exists
            HashMap<Integer,String> innerMap = connections.map.get(channel);
            if(!innerMap.containsKey(connectionId)){  // check if the user is not allready subscibe the channel. 
                innerMap.put(connectionId,subscriprionID);
                user.UserChannels.put(subscriprionID,channel);
            }
        }
        else if(connections.map.containsKey(reverseChannel)){
            HashMap<Integer,String> innerMap = connections.map.get(reverseChannel);
                if(!innerMap.containsKey(connectionId)){
                    innerMap.put(connectionId,subscriprionID);
                    user.UserChannels.put(subscriprionID,reverseChannel);
                }
        }
        else{
            HashMap<Integer,String> newChannel = new HashMap<Integer, String>();
            newChannel.put(connectionId, subscriprionID);
            connections.map.put(channel,newChannel);
            user.UserChannels.put(subscriprionID,channel);
        }

        String receipt = "RECEIPT\nreceipt-id:" + receiptID +"\n\n\u0000";
        return receipt;
    }

    private String handleUnSubscribe(Frame<T> frame){
        User user = connections.getUser(connectionId);
        String subscriprionID = (String)frame.headers.get("id");
        String channel = user.getChannel(subscriprionID);
        connections.map.get(channel).remove(connectionId,subscriprionID); //remove from the map.
        user.UserChannels.remove(subscriprionID, channel); //remove from the users channels.
        String receiptID = (String)frame.headers.get("receipt");
        return "RECEIPT\nreceipt-id:" + receiptID +"\n\n\u0000";
    }
    // private boolean checkSubscribeHeaders(Frame frame){
    //     String channel = (String)frame.headers.get("destination");

    // }

    public static void main(String[] args) {

        // //SUBSSCRIBE testing
        // StompMessagingProtocolImpl<String> protocol = new StompMessagingProtocolImpl<>();
        // ConnectionsImpl<String> connections = new ConnectionsImpl<>();
        // protocol.start(0, connections);
        // String subscribeFrame ="SUBSCRIBE\ndestination:/germany_spain\nid:17\nreceipt:73\n\n\u0000";
        // User user = new User();
        // connections.connectionIdToUsers.put(0, user);
        // HashMap<Integer,String> innerMap = new HashMap<>();
        // innerMap.put(1, "666666");
        // HashMap<Integer,String> innerMap2 = new HashMap<>();
        // innerMap2.put(2012, "1958");
        // connections.map.put("spain_/germany", innerMap);
        // connections.map.put("/germany_spain",innerMap2);
        // protocol.process(subscribeFrame);
        // System.out.println("Subscribe Map - "+ connections.map);
        // System.out.println("Subscribe UserChannels - " + user.UserChannels );
        // System.out.println("Subscribe connectionIdToUsers - " + connections.connectionIdToUsers);


        // //UnSubscribe testing
        // String unSubscribeFrame = "UNSUBSCRIBE\nid:17\nreceipt:82\n\n\u0000";
        // protocol.process(unSubscribeFrame);
        // System.out.println("UnSubscribe Map - "+ connections.map);
        // System.out.println("UnSubscribe UserChannels - " + user.UserChannels );
        // System.out.println("UnSubscribe connectionIdToUsers - " + connections.connectionIdToUsers);

    }
}
