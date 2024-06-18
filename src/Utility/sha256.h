#pragma once
#include <WString.h>
#include <mbedtls/md.h>
#include <stdio.h>

String GenerateSHA256(const String& input)
{
  uint8_t shaResult[32];
  mbedtls_md_context_t ctx;
  mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256;
 
  const size_t inputLength = input.length();       
 
  mbedtls_md_init(&ctx);
  mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 1);
  mbedtls_md_starts(&ctx);
  mbedtls_md_update(&ctx, (const unsigned char *) input.c_str(), inputLength);
  mbedtls_md_finish(&ctx, shaResult);
  mbedtls_md_free(&ctx);
  
  String output;
  for(int i= 0; i< sizeof(shaResult); i++){
      char str[3];
      sprintf(str, "%02x", (int)shaResult[i]);
      output+=str;
  }

  return output;
}