/*************************************************************************
    > File Name: main.c
    > Author: linengier
    > Mail: linengier@126.com 
    > Created Time: 2016年10月18日 星期二 14时15分43秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cjson.h"
char * makeJson()
{
    int iSize = 5;
    int i = 0;
    cJSON * pJsonRoot = NULL;

    pJsonRoot = cJSON_CreateObject();
    if(NULL == pJsonRoot)
    {
        return NULL;
    }
    cJSON_AddStringToObject(pJsonRoot, "hello", "hello world");
    cJSON_AddNumberToObject(pJsonRoot, "number", 10010);
    cJSON_AddBoolToObject(pJsonRoot, "bool", 1);
    
    /*create sub*/
    cJSON * pSubJson = NULL;
    pSubJson = cJSON_CreateObject();
    if(NULL == pSubJson)
    {
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
    cJSON_AddStringToObject(pSubJson, "subjsonobj", "a sub json string");
    cJSON_AddItemToObject(pJsonRoot, "subobj", pSubJson);

    cJSON * root =  cJSON_CreateArray();                                                             
    if(NULL == root)
    {
        printf("create json array faild\n");
        return NULL;
    }
    
    for(i = 0; i < iSize; i++)
    {
        cJSON_AddNumberToObject(root, "hehe", i);
    }
    cJSON_AddItemToObject(pJsonRoot, "array", root);
    char * p = cJSON_Print(pJsonRoot);
    if(NULL == p)
    {
        //convert json list to string faild, exit
        //because sub json pSubJson han been add to pJsonRoot, so just delete pJsonRoot, if you also delete pSubJson, it will coredump, and error is : double free
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
   
    cJSON_Delete(pJsonRoot);
    return p;
}

void parseJson(char * pMsg)
{
    if(NULL == pMsg)
    {
        return;
    }
    cJSON * pJson = cJSON_Parse(pMsg);
    if(NULL == pJson)                                                                                          {
        // parse faild, return
      return ;
    }

    // get string from json
    cJSON * pSub = cJSON_GetObjectItem(pJson, "hello");
    if(NULL == pSub)
    {
    }
    printf("obj_1 : %s\n", pSub->valuestring);
    // get number from json
    pSub = cJSON_GetObjectItem(pJson, "number");
    if(NULL == pSub)
    {
    }
    printf("obj_2 : %ld\n", pSub->valueint);
    // get bool from json
    pSub = cJSON_GetObjectItem(pJson, "bool");
    if(NULL == pSub)
    {
        // get bool from json faild
    }
    printf("obj_3 : %ld\n", pSub->valueint);
    // get sub object
    pSub = cJSON_GetObjectItem(pJson, "subobj");
    if(NULL == pSub)
    {
        // get sub object faild
    }
    cJSON * pSubSub = cJSON_GetObjectItem(pSub, "subjsonobj");
    if(NULL == pSubSub)
    {
        // get object from subject object faild
    }
    printf("sub_obj_1 : %s\n", pSubSub->valuestring);

    pSub = cJSON_GetObjectItem(pJson, "array");
    int iSize = cJSON_GetArraySize(pSub);
    int iCnt;
    for(iCnt = 0; iCnt < iSize; iCnt++)
    {
        cJSON * node = cJSON_GetArrayItem(pSub, iCnt);
        if(NULL == node)
        {
            continue;
        }
        int iValue = node->valueint;
        printf("value[%2d] : [%d]\n", iCnt, iValue);
    } 
    cJSON_Delete(pJson);
}
//创建数组，数组值是另一个JSON的item，这里使用数字作为演示
char * makeArray(int iSize)
{
    cJSON * root =  cJSON_CreateArray();                                                             
    if(NULL == root)
    {
        printf("create json array faild\n");
        return NULL;
    }
    int i = 0;
    
    for(i = 0; i < iSize; i++)
    {
        cJSON_AddNumberToObject(root, "hehe", i);
    }
    char * out = cJSON_Print(root);
    cJSON_Delete(root);

    return out;
}

//解析刚刚的CJSON数组
void parseArray(char * pJson)
{
    int iCnt = 0;
    if(NULL == pJson)
    {                                                                                                
        return ;
    }
    cJSON * root = NULL;
    if((root = cJSON_Parse(pJson)) == NULL)
    {
        return ;
    }
    int iSize = cJSON_GetArraySize(root);
    for(iCnt = 0; iCnt < iSize; iCnt++)
    {
        cJSON * pSub = cJSON_GetArrayItem(root, iCnt);
        if(NULL == pSub)
        {
            continue;
        }
        int iValue = pSub->valueint;
        printf("value[%2d] : [%d]\n", iCnt, iValue);
    }   
    cJSON_Delete(root);
    return;
}
int main()
{
    char * p = makeJson();
    char * p2 = NULL;
    if(NULL == p)
    {
        return 0;
    }
    printf("%s\n", p);
    parseJson(p);
    free(p);
    printf("----------------------\r\n");
    printf("array test\r\n");
    p2 = makeArray(5);
    parseArray(p2);
    free(p2);
    return 0;
}
