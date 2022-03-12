public class PermissionEcxeption extends RuntimeException{
    PermissionEcxeption(String message){
        super((message.length()!=0) ? message : "Undefined");
    }
}
