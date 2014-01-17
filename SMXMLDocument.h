/*
 The MIT License
 
 Copyright (c) 2011 Spotlight Mobile
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE. 
*/

/*
 
 SMXMLDocument
 -------------
 Created by Nick Farina (nfarina@gmail.com)
 Version 1.0
 
 */

// SMXMLDocument is a very handy lightweight XML parser for iOS.

extern NSString *const SMXMLDocumentErrorDomain;

@class SMXMLDocument, SMXMLElementChildren, SMXMLElementValueFinder;

@interface SMXMLElement : NSObject<NSXMLParserDelegate>

@property (nonatomic, weak) SMXMLDocument *document;
@property (nonatomic, weak) SMXMLElement *parent;
@property (nonatomic, copy) NSString *name;
@property (nonatomic, retain) NSString *value;
@property (nonatomic, retain) NSArray *children;
@property (nonatomic, retain) NSDictionary *attributes;
@property (nonatomic, readonly) SMXMLElement *firstChild, *lastChild;
@property (nonatomic, readonly) SMXMLElementChildren *all;
@property (nonatomic, readonly) SMXMLElementValueFinder *values;

- (id)initWithDocument:(SMXMLDocument *)document;
- (SMXMLElement *)childNamed:(NSString *)name;
- (NSArray *)childrenNamed:(NSString *)name;
- (SMXMLElement *)childWithAttribute:(NSString *)attributeName value:(NSString *)attributeValue;
- (NSString *)attributeNamed:(NSString *)name;
- (SMXMLElement *)descendantWithPath:(NSString *)path;
- (NSString *)valueWithPath:(NSString *)path;
- (NSString *)fullDescription; // like -description, this writes the document out to an XML string, but doesn't truncate the node values.
- (NSString *)encodedDescription; // like -fullDescription, but this does HTML encoding of element content

// Literal access - personElement[0] is the same as writing [personElement.children objectAtIndex:0]
- (SMXMLElement *)objectAtIndexedSubscript:(NSUInteger)index;

// Literal access - personElement[@"FirstName"] is the same as writing [personElement childNamed:@"FirstName"]
- (SMXMLElement *)objectForKeyedSubscript:(NSString *)childName;

@end

@interface SMXMLElementChildren : NSObject

// Literal access - booksElement.all[@"book"] is the same as writing [booksElement childrenNamed:@"book"]
- (NSArray *)objectForKeyedSubscript:(NSString *)childredNamed; // Array of SMXMLElement

@end

@interface SMXMLElementValueFinder : NSObject

// Literal access - book.values[@"cover.title"] is the same as writing [book valueWithPath:@"cover.title"]
- (NSString *)objectForKeyedSubscript:(NSString *)path; // NSString

@end

@interface SMXMLDocument : SMXMLElement

@property (nonatomic, retain) NSError *error;

- (id)initWithData:(NSData *)data error:(NSError **)outError;

+ (SMXMLDocument *)documentWithData:(NSData *)data error:(NSError **)outError;

@end
