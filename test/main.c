#include <stdio.h>
#include "oauth2.h"

int main(int argc, char** argv)
{
    oauth2_config* conf = oauth2_init("1002451746530832", "58347acb5c1106f0f783af4eeff5263d");
    oauth2_set_redirect_uri(conf, "http://www.exadigm.com/");
    char* redir_uri = oauth2_request_auth_code(conf, "https://graph.facebook.com/oauth/authorize", "public_profile", "LOL");

    printf("Visit this url and hit authorize: %s\n", redir_uri);
    printf("Now put the auth token here: ");
    
    char code[555];
    scanf("%s", code);

    //Now test token based auth
    char* rv = oauth2_access_auth_code(conf, "https://graph.facebook.com/oauth/access_token", code, NULL);

    oauth2_set_auth_code(conf, rv);
    printf("Access Token: %s\n", rv);
    free(rv);

    printf("Enter your Facebook status: ");
    char status[255];
    scanf("%s", status);
    char status2[255];
    sprintf(status2, "message=%s", status);
    
    rv = oauth2_request(conf, "https://graph.facebook.com/me", status2);

    printf("%s\n", rv);

    oauth2_cleanup(conf);

    return 0;
}
