package com.team254.lib.util;

/**
 * This manages http stuff for the deta lawger
 * @author spinkerton
 * @author akalb
 * @author bg451
 * @author tombot
 */
public class HtmlResponse {
  static String OK = "HTTP/1.x 200 OK\n";
  static String PAGE_NOT_FOUND = "HTTP/1.x 404 Not Found\n\n ";
  public static String ERROR = "HTTP/1.x 400 Bad Request\n\n";
  public String connection = "Connection: close\n";
  
  public static String controlAccess = "Access-Control-Allow-Origin: http://localhost\n";
  public static String contentLength = "";

  private String data;
  private String header = OK + controlAccess;

  public HtmlResponse(String response) {
    this.data = response;
    this.contentLength = "Content-Length:" + data.length() + "\n\n";
  }

  public HtmlResponse(String response, String header) {
    this.header = header;
    this.data = response;
    this.contentLength = "Content-Length:" + data.length() + "\n\n";
  }
  
  public static HtmlResponse createResponse(String res) {
    return new HtmlResponse(res);
  }

  public static HtmlResponse createError(String res) {
    return new HtmlResponse(res, ERROR);
  }

  public String toString() {
    //System.out.println(header + contentLength);
    return header + connection + contentLength + data;
  }
  
  public static String test() {
    return OK + "<h1> Test.html page </h1>";
  }
}
