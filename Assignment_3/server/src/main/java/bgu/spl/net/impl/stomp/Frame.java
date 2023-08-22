package bgu.spl.net.impl.stomp;

import java.util.HashMap;

public class Frame<T> {

    private boolean isServer = false;
    private boolean isClient = false;
    private frameCommandType commandType = null;
    public HashMap<String,String> headers;
    private String body = "";
    private String bodyMessage = ""; // maybe we dont need this

    private void stringToCommandType(String string){
        if(string.equals("CONNECTED")){
            isServer = true;
            commandType = frameCommandType.CONNECTED;
        }
        if(string.equals("MESSAGE")){
            isServer = true;
            commandType = frameCommandType.MESSAGE;
        }
        if(string.equals("RECEIPT")){
            isServer = true;
            commandType = frameCommandType.RECEIPT;
        }
        if(string.equals("ERROR")){
            isServer = true;
            commandType = frameCommandType.ERROR;
        }
        if(string.equals("CONNECT")){
            isClient = true;
            commandType = frameCommandType.CONNECT;
        }
        if(string.equals("SEND")){
            isClient = true;
            commandType = frameCommandType.SEND;
        }
        if(string.equals("SUBSCRIBE")){
            isClient = true;
            commandType = frameCommandType.SUBSCRIBE;
        }
        if(string.equals("UNSUBSCRIBE")){
            isClient = true;
            commandType = frameCommandType.UNSUBSCRIBE;
        }
        if(string.equals("DISCONNECT")){
            isClient = true;
            commandType = frameCommandType.DISCONNECT;
        }
    }

    Frame(T frameString){

        String frameMessage = (String)frameString; 
        headers = new HashMap<>();
        String[] splittedMessage = frameMessage.split("\n");
        stringToCommandType(splittedMessage[0]);
        boolean isBody = false;
        for(int i = 1; i < splittedMessage.length; i++){
            if(!isBody && splittedMessage[i].equals("")){
                isBody = true;
            }
            if(!splittedMessage[i].equals("^@")){
                if(isBody){
                        body = body + splittedMessage[i] + "\n";
                        if(!splittedMessage[i].equals(""))
                            bodyMessage = bodyMessage + splittedMessage[i] + "\\n";
                }
                else{
                    String[] header = splittedMessage[i].split(":");
                    headers.putIfAbsent(header[0], header[1]);
                }
            }   
        }
    } 

    public boolean isServer(){
        return isServer;
    }

    public boolean isClient(){
        return isClient;
    }

    public frameCommandType getCommandType(){
        return commandType;
    }
    
    // public HashMap <String,String> getHeaders(){
    //     return headers;
    // }

    public String getBody(){
        return body;
    }

    public String getBodyMessage(){
        return bodyMessage;
    }

    public static void main(String[] args) {
        String ex = "MESSAGE\nsubscription:78\nmessage-id:20\ndestination:/topic/a^\n\nHello Topic a\nAAA\n^@";
        Frame<String> frame = new Frame(ex);
        System.out.println(frame.commandType);
        System.out.println(frame.headers.get("subscription"));
        String[] exmp = ex.split("\n");
        System.out.println("Check this: " + exmp[0] + "_" + exmp[1]);
    }
}
