//
//  SFOAuthCredentials.h
//  SalesforceOAuth
//
//  Created by Steve Holly on 17/06/2011.
//  Copyright 2011 Salesforce.com. All rights reserved.
//

#import <Foundation/Foundation.h>

/** Object representing an individual user account's logon credentials.
 
 This object represents information about a user account necessary to authenticate and
 reauthenticate against Salesforce.com servers using OAuth2. It includes information such as
 the user's account ID, the protocol to use, and any session or refresh tokens assigned
 by the server.
 
 The secure information contained in this object is persisted securely within the
 device's Keychain, and is accessed by using the `identifier` property.
 
 Instances of this object are used to begin the authentication process, by supplying
 it to an `SFOAuthCoordinator` instance which conducts the authentication workflow.
 
 The credentials stored in this object include:
 
 - Consumer key and secret

 - Request token and secret

 - Access token and secret

 @see SFOAuthCoordinator
*/
@interface SFOAuthCredentials : NSObject <NSCoding>

/** HTTP protocol scheme.

 This value must be either `http` or `https`. Defaults to `https`.
 
 @throws NSInvalidArgumentException if the value is not `http` or `https`
 */
@property (nonatomic, copy) NSString *protocol;

/** Logon host domain name.
 
 The domain used to initiate a user login, for example _login.salesforce.com_
 or _test.salesforce.com_. The default is _login.salesforce.com_.
 */
@property (nonatomic, copy) NSString *domain;

/** Client consumer key.
 
 Client ID representing the client application.
*/
@property (nonatomic, copy) NSString *clientId;

/** Callback URL to load at the end of the authentication process.
 
 This must match the callback URL in the Remote Access object exactly, or approval will fail.
*/
@property (nonatomic, copy) NSString *redirectUri;

/** Token used to refresh the user's session.
 
 This is updated by the `SFOAuthCoordinator` once the session is established.
 
 The setter for this property is exposed publicly only for unit tests. Client code should use the revoke methods instead.
 */
@property (nonatomic, copy) NSString *refreshToken;

/** The access token for the user's session.
 
 This is updated by the `SFOAuthCoordinator` whenever the session expires.
 
 The setter for this property is exposed publicly only for unit tests. Client code should use the revoke methods instead.
 */
@property (nonatomic, copy) NSString *accessToken;

/** Organization ID
 
 The setter for this property is exposed publicly only for unit tests. Client code should not set this property.
 */
@property (nonatomic, copy) NSString *organizationId;

/** The URL of the server instance for this session.
 
 This is the URL that client requests should be made to after authentication completes.
 
 The setter for this property is exposed publicly only for unit tests. Client code should not set this property.
 */
@property (nonatomic, copy) NSURL *instanceUrl;   

/** The timestamp when the session access token was issued.
 
 The setter for this property is exposed publicly only for unit tests. Client code should not set this property.
 */
@property (nonatomic, copy) NSDate *issuedAt;     

/** The identity URL for the user returned as part of a successful authentication response.
 The format of the URL is: _https://login.salesforce.com/ID/orgID/userID_ where orgId is the ID of the Salesforce organization 
 that the user belongs to, and userID is the Salesforce user ID.
 
 The setter for this property is exposed publicly only for unit tests. Client code should not set this property.
 */
@property (nonatomic, copy) NSURL *identityUrl;

/** A convenience property returning the first 15 characters of the Salesforce User ID returned in the final path component 
 of the identityUrl.
 
 The setter for this property is exposed publicly only for unit tests. Client code should not set this property.
 */
@property (nonatomic, copy) NSString *userId;

///---------------------------------------------------------------------------------------
/// @name Initialization
///---------------------------------------------------------------------------------------

/** Initializes an authentication credential object with the given client ID identifier.
 
 The `anIdentifier` argument must not be empty or `nil`, as this client ID is used to
 securely identify the account within the device's secure keychain.

 @param anIdentifier The client ID (also known as consumer key) to be used for the oauth session. 
                     The identifier may not be nil or empty.
 @return The initialized authentication credential object.
 */
- (id)initWithIdentifier:(NSString *)anIdentifier;

/** Revoke the OAuth access and refresh tokens.
 */
- (void)revoke;

/** Revoke the OAuth access token.
 */
- (void)revokeAccessToken;

/** Revoke the OAuth refresh token.
 */
- (void)revokeRefreshToken;

@end