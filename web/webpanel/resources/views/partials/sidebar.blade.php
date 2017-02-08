<li>
	<a href="{{ url('/') }}"><i class="fa fa-dashboard fa-fw"></i> Dashboard</a>
</li>

<li>
	<a href="{{ url('/accounts') }}"><i class="fa fa-users fa-fw"></i> Accounts<span class="fa arrow"></span></a>
	<ul class="nav nav-second-level">
		<li>
			<a href="{{ url('/accounts/import') }}">Andmeimport</a>
		</li>
		<li>
			<a href="{{ url('/accounts/create') }}">Loo uus kasutaja</a>
		</li>
		<li>
			<a href="{{ url('/accounts/edit') }}">Redigeeri kasutajaid</a>
		</li>
<!--
		<li>
			<a href="#">Third Level <span class="fa arrow"></span></a>
			<ul class="nav nav-third-level">
				<li>
					<a href="#">Third Level Item</a>
				</li>
				<li>
					<a href="#">Third Level Item</a>
				</li>
				<li>
					<a href="#">Third Level Item</a>
				</li>
				<li>
					<a href="#">Third Level Item</a>
				</li>
			</ul>
		</li>
-->
	</ul>
</li>

<li>
	<a href="{{ url('/cards') }}"><i class="fa fa-credit-card fa-fw"></i> Cards</a>
</li>
