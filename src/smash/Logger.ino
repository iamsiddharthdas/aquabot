//Constructor
Logger::Logger() {};

/**
   Set up the logger
*/
boolean Logger::setup( ) {
  logger = options.isLogging();
  Serial.print(F( "SETUP Logger: " )); Serial.println( logger );
  return logger;
}

void Logger::setLogger( boolean choice ) {
  logger = choice;
  //Serial.print( "options request: "); Serial.println( String( choice ));
}

void Logger::print( String msg ) {
  if ( !options.isLogging())
    return;
  //Serial.print( "log request: "); Serial.println( msg );
  options.getOptions( WebClient::LOG, msg, false);
}

void Logger::println( String msg ) {
  if ( !options.isLogging())
    return;
  //Serial.print( "log request: "); Serial.println( msg );
  options.getOptions( WebClient::LOG, msg, false);
}

/**
   Send a request log message
*/
boolean Logger::requestLog() {
  return logMessage("");
}

/**
   send a log message
*/
boolean Logger::logMessage( String message ) {
  webClient.connect();
  //Serial.print(F( "log request: ")); Serial.println( message );
  boolean result = webClient.sendHttp( WebClient::LOG, false, message );
  webClient.disconnect();
  return result;
}
