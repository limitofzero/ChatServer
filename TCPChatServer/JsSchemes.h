#pragma once
#include <string>

//содержит схемы для валидации json документа(возможно будет заменен на загрузку из текстовых документов)
namespace JsonParser
{

	//схема для авторизации пользователя
	const std::string authorizedScheme = R"(
	{
	"comment" : "Authorized schem",
	"type" : "object",
	"properties" :
	{
		"Authorizing" : 
		{
			"type" : "object",
			"properties" : 
			{
				"guid": { "$ref" : "#/definitions/guid_info" },
				"password" : { "$ref" : "#/definitions/guid_info" }
			},
			"required" : [ "guid", "password" ]
		},
		"required" : ["Authorizing"]
	},
	"additionalProperties" : false,
	"definitions" : 
	{
		"guid_info" : 
		{
			"type" : "string",
			"maxLength" : 16,
			"minLength" : 6
		}
	}
})";

	//схема для валидации текстовых сообщений от пользователя
	const std::string messageScheme = R"(
{
	"comment" : "Message schem",
	"type" : "object",
	"properties" :
	{
		"Message" : 
		{
			"type" : "object",
			"properties" : 
			{
				"guid": { "$ref" : "#/definitions/guid_info" },
				"message" : 
				{
					"type" : "string",
					"minLength" : 1,
					"maxLength" : 256
				}
			},
			
			"required" : [ "guid", "message" ]
		},
		"required" : [ "Message" ]
	},
	"additionalProperties" : false,
	"definitions" : 
	{
		"guid_info" : 
		{
			"type" : "string",
					"maxLength" : 16,
					"minLength" : 6
		}
	}
})";
}