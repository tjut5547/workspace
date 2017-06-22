from bs4 import BeautifulSoup

html_atag = """<html><body><p>Test html a tag example</p>
            <a href="http://www. allitebook.com">Home</a>
            <a href="http://www.allitebook.com/books">Books</a>
            </body>
            </html>"""
soup = BeautifulSoup(html_atag, "html5lib")
print(soup.a)