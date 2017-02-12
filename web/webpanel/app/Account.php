<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Account extends Model
{
    protected $table = 'accounts';
    protected $primaryKey = 'userID';
    protected $fillabel =[
        'firstName',
        'lastName',
        'extraName',
        'email',
        'personalCode',
        'homeAddress',
        'workAddress',
        'homePhone',
        'mobilePhone',
        'jobTitle',
        'employer',
        'comments',
        'pan',
        'businessName'
    ];


    // Gets users cards
    public function cards()
    {
        return $this -> hasMany('App\Card', 'userID');
    }

    // Gets users groups
    public function groups()
    {
        return $this -> hasMany('App\Group', 'userID');
    }

    // Gets users parents
    public function parents()
    {
        return $this -> hasMany('App\Parent', 'userID');
    }
}
