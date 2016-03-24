#pragma once
#include <string>

//содержит схемы для валидации json документа(возможно будет заменен на загрузку из текстовых документов)
namespace JsonParser
{

	//схема для авторизации пользователя
	const std::string authorizedScheme = R"(
	{
	"$schema": "http://json-schema.org/draft-04/schema#",
	"title" : "Authorizing schem",
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
		}
	},
	"required" : [ "Authorizing" ],
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
	"$schema": "http://json-schema.org/draft-04/schema#",
	"title" : "Authorized schem",
	"type" : "object",
	"properties" :
	{
		"Message" :
		{
			"type" : "object",
			"properties" :
			{
				"guid": { "$ref" : "#/definitions/guid_info" },
				"content" : 
				{
					"type" : "string",
					"maxLength" : 256,
					"minLength" : 1
				}
			},
			"required" : [ "guid", "content" ]
		}
	},
	"required" : [ "Message" ],
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