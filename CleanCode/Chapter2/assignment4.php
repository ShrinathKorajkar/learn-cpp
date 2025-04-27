<?php
class Book {
    private $title;
    private $author;
    private $locationInLibrary;

    public function __construct($title, $author, $locationInLibrary){
        $this->title = $title;
        $this->author = $author;
        $this->locationInLibrary = $locationInLibrary;
    }
 
    function getTitle() {
        return $this->title;
    }
 
    function getAuthor() {
        return $this->author;
    }
 
    function turnPage() {
        // pointer to next page
    }
 
    function getCurrentPage() {
        return "current page content";
    }
 
    function getLocation() {
        return $this->locationInLibrary;
    }

    function save() {
        $filename = '/documents/'. $this->getTitle(). ' - ' . $this->getAuthor();
        file_put_contents($filename, serialize($this));
    }
}

interface Printer {
 
    function printPage($page);
}

 
class PlainTextPrinter implements Printer {
 
    function printPage($page) {
        echo $page;
    }
 
}
 
class HtmlPrinter implements Printer {
 
    function printPage($page) {
        echo '<div style="single-page">' . $page . '</div>';
    }
}

?>