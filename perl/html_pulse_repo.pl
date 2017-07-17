use HTML::TagParser;
use URI::Fetch;

main();

sub GetAllDirFiles {
    my ($html, $path) = @_;
    my @dirs = ();
    my @files = ();
    foreach my $tag ($html->getElementsByTagName('a')) {
        my $nextFolder = $tag->getAttribute('href');
        if (($tag->innerText == $nextFolder) && 
            ($nextFolder =~ /.+\/$/)){
            if ($nextFolder =~ /^\/(.*)/) {
                $nextFolder = $1;
            }
            push @dirs, $path.$nextFolder;
            next;
        }
        if ($nextFolder =~ /.*\.rpm$/) {
            print $path.$nextFolder."\n";
            #push @files, $path.$nextFolder;
        }
    }
    return (\@dirs, \@files);
}

sub Crawl {
    my ($link) = @_;
    my @dirs = ($link);
    while (scalar(@dirs) > 0){
        my $cd = shift @dirs;
        my $res = URI::Fetch->fetch($cd);
        if ($res == undef || !$res->is_success) {
            next;
        }
        my $html = HTML::TagParser->new($res->content);
        my @temp = GetAllDirFiles($html, $cd);
        push @dirs, @{$temp[0]};
    }
}

sub main {
    #my $html = HTML::TagParser('http://repos.psecure.net/repos/');
    #Crawl('http://repos.psecure.net/repos/centos/6/');
    #Crawl('http://repos.psecure.net/repos/pulse/');
    Crawl('http://repos.psecure.net/repos/scl6/release/');
}
