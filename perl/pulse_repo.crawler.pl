use LWP::UserAgent;
#use HTTP::Request;
$ua = LWP::UserAgent->new;
$ua->agent("Hari/1.0");

sub print_members {
    my ($o) = @_;
    print "-------------------\n";
    foreach my $key (keys %$o) {
        print "$key:\n";
    }
    print "-------------------\n";
}

sub get_allhref {
    my ($content) = @_;
}

sub search {
    my($url, $regex) = @_;
    my $req = HTTP::Request->new("GET",$url);
    my $res = $ua->request($req);
    #if ($req->is_success) {
        print $res->content;
    #} else {
        print $res->status_line;
    #}
    print_members($res);
}

search('http://repos.psecure.net/repos/centos/6/src/6.4-updates/');
