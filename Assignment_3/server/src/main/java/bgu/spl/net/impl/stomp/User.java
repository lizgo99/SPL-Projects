package bgu.spl.net.impl.stomp;

import java.util.HashMap;

public class User {
    private String userName;
    private String password;
    private Integer connectionId;
    public HashMap<String,String> UserChannels = new HashMap<>(); // <SubscriptionId, channel>
    //notice that if the user is logout and login maybe we need to clear the HashMap

    public String getUserName(){
        return userName;
    }

    public String getPassword(){
        return password;
    }

    public Integer getConnectionId(){
        return connectionId;
    }

    public String getChannel(String subscriptionId){
        return UserChannels.get(subscriptionId);
    }


}
