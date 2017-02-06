<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Account extends Model
{
    protected $table = 'accounts';
    protected $primaryKey = 'userID';


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
