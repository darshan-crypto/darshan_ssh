#define LIBSSH_STATIC 0

#include"ssh.h"
int verify_host(ssh_session );
int show_remote_processes(ssh_session);

int main(){
ssh_session session =  ssh_new();

if(session==0)printf("session error");
ssh_options_set(session,SSH_OPTIONS_HOST,"test.rebex.net");
ssh_options_set(session,SSH_OPTIONS_PORT_STR,"22");
ssh_options_set(session,SSH_OPTIONS_USER,"demo");
int rc;
rc = ssh_connect(session);
if(rc==SSH_OK)printf("connected\n");
if(verify_host(session)<0)printf("error verification");
// char *password =getpass("Password");
//ssh_userauth_password(session,"darshan","darshan0");
// int r = ssh_userauth_publickey_auto(session,"darsh/an","darshan0");
// if(r == SSH_AUTH_ERROR)printf("error authentication");
// if(r == SSH_AUTH_DENIED)printf("sucess");
// kbdauth(session);
// ssh_userauth_none(session,"darshan");
// int m = ssh_userauth_list(session,0);
// if(m==)
// authenticate_kbdint(session);
// ssh_key key;
// printf("\n%s",ssh_get_hmac_in(session));
// printf("\n%s",ssh_get_hmac_out(session));
// printf("\n%s",ssh_get_error(session));
// // show_remote_processes(session);
//  ssh_get_server_publickey(session,&key);
// if(ssh_key_is_public(key)==1){
//   ssh_pki_export_pubkey_file(key,"m.key");
// }
// ssh_userauth_none(session,"demo");

//   printf("autentication sucess\n");
//   int x = ssh_userauth_list(session,"demo");
  
//   if (x==SSH_AUTH_METHOD_PASSWORD||SSH_AUTH_METHOD_INTERACTIVE||SSH_AUTH_METHOD_HOSTBASED)
//   {
//     printf("a1");
//   }
  
authenticate_kbdint(session);
show_remote_processes(session);
 printf("error %s",ssh_get_error(session));
    return 0;
}

int verify_host(ssh_session s){
ssh_key pubkey;
size_t len;
int x;
unsigned char *hash;
enum ssh_known_hosts_e stat;
x = ssh_get_server_publickey(s,&pubkey);
if(x<0)return -1;
x = ssh_get_publickey_hash(pubkey,SSH_PUBLICKEY_HASH_SHA1,&hash,&len);
if(x<0)return -1;
return 1;

}
int show_remote_processes(ssh_session session)
{
  ssh_channel channel;
  int rc;
  char buffer[256];
  int nbytes;
  channel = ssh_channel_new(session);
  if (channel == NULL)
    return SSH_ERROR;
  rc = ssh_channel_open_session(channel);
  if (rc != SSH_OK)
  {
    ssh_channel_free(channel);
    return rc;
  }
  rc = ssh_channel_request_exec(channel, "uname");
  if (rc != SSH_OK)
  {
    ssh_channel_close(channel);
    ssh_channel_free(channel);
    return rc;
  }
  nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
  while (nbytes > 0)
  {
    if (write(1, buffer, nbytes) != (unsigned int) nbytes)
    {
      ssh_channel_close(channel);
      ssh_channel_free(channel);
      return SSH_ERROR;
    }
    nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
  }
  if (nbytes < 0)
  {
    ssh_channel_close(channel);
    ssh_channel_free(channel);
    return SSH_ERROR;
  }
  ssh_channel_send_eof(channel);
  ssh_channel_close(channel);
  ssh_channel_free(channel);
  return SSH_OK;
}